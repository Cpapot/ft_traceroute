/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:02:36 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/28 11:28:47 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connection.h"

/**
 * @brief Resolves a hostname to its IP address
 * @param host Hostname string to resolve
 * @return IP address as a string or NULL if resolution fails
 */
char *resolve_host(const char *host)
{
	struct addrinfo hints, *res;
	struct sockaddr_in *addr;
	char *result;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host, NULL, &hints, &res) != 0)
		return NULL;

	addr = (struct sockaddr_in *)res->ai_addr;
	result = inet_ntoa(addr->sin_addr);
	freeaddrinfo(res);
	return result;
}

/**
 * @brief Resolves an IP address to a hostname through reverse DNS lookup
 * @param ip IP address string to resolve
 * @param allocatedData Double pointer to memory management list for tracking allocations
 * @return Hostname as a string or the original IP if resolution fails
 */
char *resolve_ip(char *ip, t_memlist **allocatedData)
{
	struct sockaddr_in sa;
	char host[254];
	char *result;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &sa.sin_addr);

	int res = getnameinfo((struct sockaddr *)&sa, sizeof(sa), host, sizeof(host), NULL, 0, NI_NAMEREQD);

	if (res != 0)
	{
		ft_strlcpy(host, ip, sizeof(host) - 1);
		host[sizeof(host) - 1] = '\0';
	}

	result = stock_malloc(ft_strlen(host) + 1, allocatedData);
	if (result == NULL)
	{
		perror("malloc");
		return ip;
	}
	ft_strlcpy(result, host, ft_strlen(host) + 1);
	return result;
}

/**
 * @brief Calculates the Internet checksum for ICMP packets
 * @param b Pointer to the data to calculate checksum for
 * @param len Length of the data in bytes
 * @return 16-bit checksum value
 */
unsigned short checksum(void *b, int len)
{
	unsigned short *buf = b;
	unsigned int sum = 0;
	unsigned short result;

	for (sum = 0; len > 1; len -= 2)
		sum += *buf++;
	if (len == 1)
		sum += *(unsigned char *)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

/**
 * @brief Updates ICMP packet data with new sequence number and TTL value
 * @param data Pointer to traceroute data structure
 * @param net_data Pointer to network data structure
 */
void update_data(t_traceroutedata *data, t_network_data *net_data)
{
	net_data->dest_port = 33434 + data->seq;
	setsockopt(net_data->socket, IPPROTO_IP, IP_TTL, &data->ttl, sizeof(data->ttl));
	net_data->addr.sin_port = htons(net_data->dest_port);
}

/**
 * @brief Sets up the network socket and connection for traceroute
 * @param data Pointer to traceroute data structure
 * @return Pointer to initialized network data structure or NULL on failure
 */
t_network_data *setup_connection(t_traceroutedata *data)
{
	t_network_data *net_data;

	net_data = stock_malloc(sizeof(t_network_data), &data->allocatedData);
	if (net_data == NULL)
		return sprintf(data->error, "malloc, %s", strerror(errno)), NULL;

	net_data->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (net_data->socket < 0)
		return sprintf(data->error, "UDP socket, %s", strerror(errno)), NULL;

	net_data->recv_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (net_data->recv_socket < 0)
		return sprintf(data->error, "ICMP socket, %s", strerror(errno)), NULL;

	net_data->addr_len = sizeof(net_data->r_addr);

	ft_bzero(&net_data->addr, sizeof(net_data->addr));
	net_data->addr.sin_family = AF_INET;
	inet_pton(AF_INET, data->targetIP, &net_data->addr.sin_addr);
	net_data->dest_port = 33434;
	net_data->tv_out.tv_sec = RECV_TIMEOUT;
	net_data->tv_out.tv_usec = 0;
	setsockopt(net_data->recv_socket, SOL_SOCKET, SO_RCVTIMEO,
			   (const char *)&net_data->tv_out, sizeof(net_data->tv_out));

	data->ttl = 0;
	data->hops = 0;
	return net_data;
}

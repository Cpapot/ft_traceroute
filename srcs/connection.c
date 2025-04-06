/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:02:36 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/06 22:14:03 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connection.h"

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

char *resolve_ip(char *ip, t_memlist **allocatedData)
{
	struct sockaddr_in sa;
	char host[254];
	char *result;

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &sa.sin_addr);

	int res = getnameinfo((struct sockaddr *)&sa, sizeof(sa), host, sizeof(host), NULL, 0, NI_NAMEREQD);

	if (res != 0)
	{
		strncpy(host, ip, sizeof(host) - 1);
		host[sizeof(host) - 1] = '\0';
	}

	result = stock_malloc(strlen(host) + 1, allocatedData);
	if (result == NULL)
	{
		perror("malloc");
		return ip;
	}
	strcpy(result, host);
	return result;
}

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

void update_data(t_traceroutedata *data, t_network_data *net_data)
{
	ft_bzero(&net_data->packet, sizeof(net_data->packet));
	net_data->icmp = (struct icmphdr *)net_data->packet;
	net_data->icmp->type = ICMP_ECHO;
	net_data->icmp->code = 0;
	net_data->icmp->un.echo.sequence = htons(++data->seq);
	net_data->icmp->un.echo.id = htons(getpid());
	net_data->icmp->checksum = 0;
	net_data->icmp->checksum = checksum(net_data->packet, sizeof(struct icmphdr));

	setsockopt(net_data->socket, IPPROTO_IP, IP_TTL, &data->ttl, sizeof(data->ttl));
}

t_network_data *setup_connection(t_traceroutedata *data)
{
	t_network_data *net_data;

	net_data = stock_malloc(sizeof(t_network_data), &data->allocatedData);
	if (net_data == NULL)
		return sprintf(data->error, "malloc, %s", strerror(errno)), NULL;
	net_data->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (net_data->socket < 0)
		return sprintf(data->error, "sockect, %s", strerror(errno)), NULL;

	net_data->icmp = (struct icmphdr *)net_data->packet;
	net_data->addr_len = sizeof(net_data->r_addr);

	ft_bzero(&net_data->addr, sizeof(net_data->addr));
	net_data->addr.sin_family = AF_INET;
	net_data->addr.sin_addr.s_addr = inet_addr(data->targetIP);

	net_data->tv_out.tv_sec = RECV_TIMEOUT;
	net_data->tv_out.tv_usec = 0;
	setsockopt(net_data->socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&net_data->tv_out, sizeof(net_data->tv_out));

	data->ttl = 0;
	data->hops = 0;
	return net_data;
}

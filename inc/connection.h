/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:01:42 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/28 11:22:44 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_H
# define CONNECTION_H

# include "ft_traceroute.h"

# include <stdlib.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/ip_icmp.h>
# include <netinet/ip.h>
# include <netinet/in.h>
# include <string.h>
# include <time.h>

#define RECV_TIMEOUT 1

typedef struct s_network_data
{
	int					socket;
	int					recv_socket;
	char				packet[64];
	struct sockaddr_in	addr;
	struct sockaddr_in	r_addr;
	socklen_t			addr_len;
	struct ip			*ip_header;
	struct icmphdr		*icmp_header;
	struct timeval		tv_out;
	uint16_t			dest_port;
}	t_network_data;

t_network_data	*setup_connection(t_traceroutedata *data);
void			update_data(t_traceroutedata *data, t_network_data *net_data);
unsigned short	checksum(void *b, int len);

#endif

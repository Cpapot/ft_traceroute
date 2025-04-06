/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:11:58 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/06 23:09:43 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include "connection.h"
#include "parsing.h"
#include "timer.h"
#include <signal.h>

bool loop = true;

void close_traceroute(t_traceroutedata *data, t_network_data *net_data, int status)
{
	if (net_data != NULL)
		close(net_data->socket);
	stock_free(&data->allocatedData);
	exit(status);
}

void handler(int signal)
{
	(void)signal;
	loop = false;
}

int main_loop(t_traceroutedata *data, t_network_data *net_data)
{
	char			*lastIP = NULL;
	t_memlist		*allocatedData = NULL;

	while (loop && data->hops < data->maxHops)
	{
		if (data->hops == data->maxHops)
		{
			printf("Reached max hops\n");
			break;
		}

		data->ttl++;
		data->hops++;

		printf("%s%d  ", (data->hops >= 10 ? "" : " "), data->hops);

		for (unsigned int i = 0; i < data->tryPerHop; i++)
		{
			update_data(data, net_data);
			init_timer();

			if (sendto(net_data->socket, net_data->packet, sizeof(net_data->packet), 0,
					   (struct sockaddr *)&(net_data->addr), sizeof(net_data->addr)) <= 0)
			{
				perror("sendto");
				close_traceroute(data, net_data, 1);
			}

			int ret = recvfrom(net_data->socket, net_data->packet, sizeof(net_data->packet), 0,
							   (struct sockaddr *)&(net_data->r_addr), &(net_data->addr_len));
			if (ret <= 0)
			{
				long double delay = stop_timer();
				(void)delay;
				printf("* ");
			}
			else
			{
				long double delay = stop_timer();
				char *currentIP = ft_strdup(inet_ntoa(net_data->r_addr.sin_addr), &allocatedData);
				if (currentIP == NULL)
				{
					perror("strdup");
					close_traceroute(data, net_data, 1);
				}
				if (lastIP == NULL || (lastIP != NULL && strcmp(currentIP, lastIP) != 0))
				{
					char *resolved = resolve_ip(currentIP, &allocatedData);
					printf("%s (%s) %.3Lf ms  ", resolved, currentIP, delay);
					lastIP = currentIP;
				}
				else
				{
					printf("%.3Lf ms  ", delay);
				}
			}
			usleep(100000);
		}
		if (lastIP != NULL && !(lastIP && strcmp(data->targetIP, lastIP)))
		{
			printf("\n");
			stock_free(&allocatedData);
			return (1);
		}
		sleep(1);
		lastIP = NULL;
		printf("\n");
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_traceroutedata data;
	t_network_data *net_data = NULL;

	data.allocatedData = NULL;
	data.address = NULL;
	data.targetIP = NULL;
	data.maxHops = 30;
	data.tryPerHop = 3;
	data.seq = 0;
	ft_bzero(data.error, ERROR_BUFFSIZE);

	// parsing & resolve host
	if (parseParameter(argc, argv, &data) != SUCCES)
	{
		printf("Error: %s\n", data.error);
		close_traceroute(&data, net_data, 1);
	} // remplacer par fonction error

	printf(PR_INFO, data.address, data.targetIP, data.maxHops, 60);

	signal(SIGINT, handler);

	net_data = setup_connection(&data);
	if (net_data == NULL)
	{
		printf("Error: %s\n", data.error);
		close_traceroute(&data, net_data, 1);
	} // remplacer par fonction error

	if (setup_timer(&data))
	{
		printf("Error: %s\n", data.error);
		close_traceroute(&data, net_data, 1);
	} // remplacer par fonction error

	main_loop(&data, net_data);

	close_traceroute(&data, net_data, 0);
}

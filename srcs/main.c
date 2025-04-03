/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:11:58 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/20 20:27:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include "connection.h"
#include "parsing.h"
#include <signal.h>

bool loop = true;

void close_traceroute(t_traceroutedata *data, t_network_data *net_data, int status)
{
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
	while (loop && data->hops < data->maxHops)
	{
		if (data->hops == data->maxHops)
		{
			printf("Reached max hops\n");
			break;
		}

		
		// on envoie le paquet et on regarde la destination sur lerreur time to live exceeded
		// on print les infos

		// si on a atteint la destination on print et on quitte
		update_data(data, net_data);
	}
	return (0);
}


int main(int argc, char **argv)
{
	t_traceroutedata data;
	t_network_data *net_data;

	data.allocatedData = NULL;
	data.address = NULL;
	data.targetIP = NULL;
	data.maxHops = 30;
	ft_bzero(data.error, ERROR_BUFFSIZE);

	// parsing & resolve host
	if (parseParameter(argc, argv, &data) != SUCCES)
	{
		printf("Error: %s\n", data.error);
		close_traceroute(&data, &net_data, 1);
	} // remplacer par fonction error

	printf("%s\n", data.address);
	printf("%s\n", data.targetIP);

	signal(SIGINT, handler);

	net_data = setup_connection(&data);
	if (net_data == NULL)
	{
		printf("Error: %s\n", data.error);
		close_traceroute(&data, &net_data, 1);
	} // remplacer par fonction error

	if (setup_timer(&data))
	{
		printf("Error: %s\n", data.error);
		close_traceroute(&data, &net_data, 1);
	} // remplacer par fonction error

	main_loop(&data, net_data); 
}

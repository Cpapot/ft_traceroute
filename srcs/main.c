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

void close_traceroute(t_traceroutedata *data, t_network_data *net_data, int status)
{
	close(net_data->socket);
	stock_free(&data->allocatedData);
	exit(status);
}

int main(int argc, char **argv)
{
	t_traceroutedata data;
	t_network_data net_data;

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
	}
	printf("%s\n", data.address);
	printf("%s\n", data.targetIP);

	
	// create socket ect

	// ttl = 1
	// loop on max hops
	// on envoie le paquet et on regarde la destination sur lerreur time to live exceeded
	// on print les infos


	// si on a atteint la destination on print et on quitte 
}

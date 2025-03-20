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


void close_traceroute(t_traceroutedata *data, t_network_data *net_data, int status)
{
	close(net_data->socket);
	stock_free(&data->allocatedData);
	exit(status);
}

int main()
{
	ft_printf("Hello World\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:17:35 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/28 10:56:02 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "connection.h"


char	*resolve_host(const char *host);
void	close_traceroute(t_traceroutedata *data, t_network_data *net_data, int status);

int checkFlags(char *flags_line, t_traceroutedata *data)
{
	if (!ft_strcmp(flags_line, "--help") == 0)
	{
		printf("Usage: ft_traceroute [options] <host>\n");
		close_traceroute(data, NULL, 0);
	}
	else
		return parser_set_error(INVALID_FLAG, flags_line, data);
	return 0;
}

/**
 * @brief Parses command-line arguments for the traceroute program
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @param data Pointer to traceroute data structure to store parsed information
 * @return SUCCES on successful parsing, error code otherwise
 */
int parseParameter(int argc, char **argv, t_traceroutedata *data)
{
	int addressIndex = 0;

	for (int i = 1; i != argc; i++)
	{
		if (isFlags(argv[i]))
		{
			if (checkFlags(argv[i], data))
				return INVALID_FLAG;
		}
		else if (addressIndex == 0)
		{
			addressIndex = i;
			data->address = argv[i];
		}
	}
	if (addressIndex == 0)
		return parser_set_error(NO_HOST, 0, data);
	data->targetIP = ft_strdup(resolve_host(argv[addressIndex]), &data->allocatedData);
	if (data->targetIP == NULL)
		return parser_set_error(UNKNOWN_HOST, 0, data);
	return SUCCES;
}

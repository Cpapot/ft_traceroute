/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:17:35 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/20 20:39:09 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *resolve_host(const char *host);
void help_flag(t_traceroutedata *data);

// int checkFlags(char *flags_line, t_traceroutedata *data)
// {
// 	for (int i = 0; flags_line[i]; i++)
// 	{
// 		if (!isInString(flags_line[i], VALIDFLAGS))
// 			return parser_set_error(INVALID_FLAG, flags_line[i], data);
// 		switch (flags_line[i])
// 		{

// 		case '?':
// 			help_flag(data);
// 			break;
// 		}
// 	}
// 	return 0;
// }

int parseParameter(int argc, char **argv, t_traceroutedata *data)
{
	int addressIndex = 0;

	for (int i = 1; i != argc; i++)
	{
		if (isFlags(argv[i]))
		{
			// if (checkFlags(ft_stsubstr(argv[i], 1, ft_strlen(argv[i]) - 1, &data->allocatedData), data))
			// 	return INVALID_FLAG;
			printf("%s", argv[i]);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:23:03 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/20 20:23:15 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	isInString(char a, char *str)
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == a)
			return true;
	}
	return false;
}

bool	isFlags(char *str)
{
	if (str != NULL)
	{
		if (str[0] == '-' && ft_strlen(str) >= 2)
			return true;
	}
	return false;
}

int		parser_set_error(int error_code, char invalidFlag, t_traceroutedata *data)
{
	switch (error_code)
	{
	case NO_HOST:
		sprintf(data->error, ERR_MISSHOST);
		break;
	case INVALID_FLAG:
		sprintf(data->error, ERR_INVFLAG, invalidFlag);
		break;
	case UNKNOWN_HOST:
		sprintf(data->error, ERR_UNKNHOST);
	}
	return 1;
}

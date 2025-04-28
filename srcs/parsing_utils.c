/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:23:03 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/28 09:51:14 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Checks if a character exists within a string
 * @param a Character to search for
 * @param str String to search within
 * @return true if character is found, false otherwise
 */
bool	isInString(char a, char *str)
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == a)
			return true;
	}
	return false;
}

/**
 * @brief Determines if a string represents a command-line flag
 * @param str String to check
 * @return true if string starts with '-' and has at least 2 characters, false otherwise
 */
bool	isFlags(char *str)
{
	if (str != NULL)
	{
		if (str[0] == '-' && ft_strlen(str) >= 2)
			return true;
	}
	return false;
}

/**
 * @brief Sets appropriate error message in data structure based on error code
 * @param error_code Error code indicating type of error (NO_HOST, INVALID_FLAG, UNKNOWN_HOST)
 * @param invalidFlag Character representing the invalid flag (used when error_code is INVALID_FLAG)
 * @param data Pointer to traceroute data structure for storing the error message
 * @return Always returns 1 to indicate an error occurred
 */
int		parser_set_error(int error_code, char *invalidFlag, t_traceroutedata *data)
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

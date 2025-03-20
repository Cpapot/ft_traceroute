/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:18:09 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/20 20:21:49 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "ft_traceroute.h"

/*				parser	error				*/
# define ERR_MISSHOST	"missing host operand"
# define ERR_UNKNHOST	"unknown host"
# define ERR_INVFLAG	"invalid option -- \'%c\'"

enum	e_parsing_return {
	SUCCES = 0,
	NO_HOST = 1,
	INVALID_FLAG = 2,
	UNKNOWN_HOST = 3
};

bool	isInString(char a, char *str);
bool	isFlags(char *str);
int		parser_set_error(int error_code, char invalidFlag, t_traceroutedata *data);

#endif

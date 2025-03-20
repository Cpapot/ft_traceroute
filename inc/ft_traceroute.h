/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:12:05 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/20 19:06:57 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTTRACEROUTE_H
#define FTTRACEROUTE_H

# include "../libft/includes/libft.h"
# include <stdio.h>

# define ERROR_BUFFSIZE 1024
typedef struct s_traceroutedata
{
	char			*address;
	char			*targetIP;
	int				ttl;
	int				sequence;
	t_memlist		*allocatedData;
	char			error[ERROR_BUFFSIZE];
} t_traceroutedata;

#endif

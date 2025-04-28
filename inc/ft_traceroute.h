/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:12:05 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/28 09:55:52 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTTRACEROUTE_H
# define FTTRACEROUTE_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>


# define ERROR_BUFFSIZE		1024

# define PR_INFO			"traceroute to %s (%s), %d hops max, %d byte packets\n"

typedef struct s_traceroutedata
{
	char			*address;
	char			*targetIP;
	unsigned int	seq;
	unsigned int	tryPerHop;
	unsigned int	maxHops;
	unsigned int	ttl;
	unsigned int	hops;
	t_memlist		*allocatedData;
	char			error[ERROR_BUFFSIZE];
} t_traceroutedata;

char	*resolve_ip(char *ip, t_memlist **allocatedData);

#endif

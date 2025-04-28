/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:55:18 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/28 11:53:29 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

# include "ft_traceroute.h"
# include <time.h>
# include <sys/time.h>
# include <math.h>

enum	e_time_info
{
	MIN_DEL = 0,
	MAX_DEL,
	AVG_DEL,
	DEV_DEL
};

typedef struct s_variance
{
	int				n;
	long double		sum;
	long double		sum_sqr;
} t_variance;

typedef struct s_time_data
{
	long double		actual_delay;
	long double		min_delay;
	long double		max_delay;
	t_variance		variance_data;
	long double		total_delay;
} t_time_data;

void		init_variance(t_variance *data);
void		add_variance_sample(t_variance *data, long double sample);
int			setup_timer(t_traceroutedata *data);
void 		init_timer(void);
long double	stop_timer(void);


#endif

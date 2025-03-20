/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:54:00 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/20 18:54:03 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"

void init_variance(t_variance *data)
{
	data->n = 0;
	data->sum = 0.0;
	data->sum_sqr = 0.0;
}

void add_variance_sample(t_variance *data, long double sample)
{
	data->n++;
	data->sum += sample;
	data->sum_sqr += sample * sample;
}

long double compute_stddev(t_variance *data)
{
	if (data->n == 0)
		return 0;
	long double avg = data->sum / data->n;
	return sqrtl((data->sum_sqr / data->n) - (avg * avg));
}

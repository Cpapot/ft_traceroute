/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:53:41 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/20 19:00:39 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"

t_time_data *time_data = NULL;

int setup_timer(t_traceroutedata *data)
{
	if (time_data == NULL)
	{
		time_data = stock_malloc(sizeof(t_time_data), &data->allocatedData);
		if (time_data == NULL)
			return sprintf(data->error, "malloc, broken malloc"), 1;
		time_data->max_delay = -1;
		time_data->min_delay = -1;
		time_data->total_delay = 0;
		init_variance(&time_data->variance_data);
	}
	return 0;
}

void init_timer(void)
{
	struct timeval timer;

	gettimeofday(&timer, NULL);
	time_data->actual_delay = (long double)(timer.tv_usec * 0.001 + timer.tv_sec * 1000);
}

long double stop_timer(void)
{
	struct timeval timer;

	gettimeofday(&timer, NULL);
	time_data->actual_delay = (long double)((timer.tv_usec * 0.001 + timer.tv_sec * 1000)) - time_data->actual_delay;
	if (time_data->max_delay == -1 || time_data->max_delay < time_data->actual_delay)
		time_data->max_delay = time_data->actual_delay;
	if (time_data->min_delay == -1 || time_data->min_delay > time_data->actual_delay)
		time_data->min_delay = time_data->actual_delay;
	time_data->total_delay += time_data->actual_delay;
	add_variance_sample(&time_data->variance_data, time_data->actual_delay);
	return time_data->actual_delay;
}

void get_timer_result(long double *timer_result)
{
	timer_result[MIN_DEL] = time_data->min_delay;
	timer_result[MAX_DEL] = time_data->max_delay;
	timer_result[DEV_DEL] = compute_stddev(&time_data->variance_data);
}

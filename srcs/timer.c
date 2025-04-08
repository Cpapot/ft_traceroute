/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:53:41 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/08 17:34:30 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"

t_time_data *time_data = NULL;

/**
 * @brief Initializes the timer data structure for tracking packet timing
 * @param data Pointer to traceroute data structure for memory allocation tracking
 * @return 0 on success, 1 on allocation failure
 */
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

/**
 * @brief Starts a timing operation by capturing the current time
 */
void init_timer(void)
{
	struct timeval timer;

	gettimeofday(&timer, NULL);
	time_data->actual_delay = (long double)(timer.tv_usec * 0.001 + timer.tv_sec * 1000);
}

/**
 * @brief Stops timing operation and calculates elapsed time since init_timer call
 * @return Elapsed time in milliseconds
 */
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

/**
 * @brief Retrieves timing statistics and stores them in the provided array
 * @param timer_result Array to store min delay, max delay, and standard deviation
 */
void get_timer_result(long double *timer_result)
{
	timer_result[MIN_DEL] = time_data->min_delay;
	timer_result[MAX_DEL] = time_data->max_delay;
	timer_result[DEV_DEL] = compute_stddev(&time_data->variance_data);
}

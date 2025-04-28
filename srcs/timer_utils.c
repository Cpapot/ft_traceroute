/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:54:00 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/28 10:51:03 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"

/**
 * @brief Initializes a variance calculation data structure
 * @param data Pointer to variance data structure to initialize
 */
void init_variance(t_variance *data)
{
	data->n = 0;
	data->sum = 0.0;
	data->sum_sqr = 0.0;
}

/**
 * @brief Adds a new sample to the variance calculation
 * @param data Pointer to variance data structure
 * @param sample New time sample value to add
 */
void add_variance_sample(t_variance *data, long double sample)
{
	data->n++;
	data->sum += sample;
	data->sum_sqr += sample * sample;
}

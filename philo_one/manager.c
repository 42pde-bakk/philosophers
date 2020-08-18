/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:39:21 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/19 00:40:00 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mr_manager(t_philo *philosophers, t_data *data)
{
	int		i;

	i = 0;
	while (1)
	{
		// pthread_mutex_lock(&philosophers[i].time_elapsed_mutex);
		if (get_time_ms() - philosophers[i].last_ate >=
			(unsigned long)data->time_to_die) {
			philosopher_write(&philosophers[i], "has died");
			return (1);
		}
		// pthread_mutex_unlock(&philosophers[i].time_elapsed_mutex);
		// if (philosophers[i].state != ALIVE)
		// 	return (1);
		++i;
		if (i >= data->nb_phil)
			i = 0;
	}
	return (0);
}

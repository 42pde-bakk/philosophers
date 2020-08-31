/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:39:21 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/31 11:53:20 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mr_manager(t_philo *philosophers, t_data *data)
{
	int		i;

	i = 0;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&philosophers[i].last_ate_mutex);
		if (get_time_ms() - philosophers[i].last_ate >=
			(unsigned long)data->time_to_die)
		{
			pthread_mutex_lock(&data->state_mutex);
			if (data->state != DONE)
				data->state = DEAD;
			if (data->state == DEAD)
				philosopher_write(&philosophers[i], "has died");
			pthread_mutex_unlock(&data->state_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philosophers[i].last_ate_mutex);
		++i;
		if (i >= data->nb_phil)
			i = 0;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:39:21 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/22 22:37:31 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mr_manager(t_philo *philosophers, t_data *data)
{
	int		i;

	i = 0;
	while (1)
	{
		sem_wait(data->state_sem);
		if (get_time_ms() - philosophers[i].last_ate >=
			(unsigned long)data->time_to_die)
		{
			if (data->state != DONE)
				data->state = DEAD;
			if (data->state == DEAD)
				philosopher_write(&philosophers[i], "has died");
			sem_post(data->state_sem);
			return (1);
		}
		sem_post(data->state_sem);
		++i;
		if (i >= data->nb_phil)
			i = 0;
	}
	return (0);
}

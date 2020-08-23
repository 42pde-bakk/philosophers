/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:39:21 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/23 18:36:38 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	genocide(t_data *data)
{
	int i;

	i = 0;
	sem_wait(data->finished);
	sem_wait(data->pen);
	while (data->pids[i])
	{
		kill(data->pids[i], SIGTERM);
		++i;
	}
	i = 0;
	while (data->pids[i])
	{
		waitpid(data->pids[i], NULL, 0);
		++i;
	}
}

void	*mr_manager(void *param)
{
	t_philo	*phil;

	phil = param;
	usleep(50);
	while (1)
	{
		sem_wait(phil->state_sem);
		if (get_time_ms() - phil->last_ate >=
			(unsigned long)phil->data->time_to_die)
		{
			philosopher_write(phil, "has died");
			sem_post(phil->data->finished);
			return (0);
		}
		sem_post(phil->state_sem);
		usleep(50);
	}
	return (0);
}

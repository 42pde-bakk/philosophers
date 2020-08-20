/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:39:21 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/20 21:15:17 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	genocide(t_data *data)
{
	int i;

	i = 0;
	sem_wait(data->finished);
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
	return ;
}

void*	mr_manager(void *param)
{
	t_philo	*phil;

	phil = param;
	while (1)
	{
		sem_wait(phil->check);
		if (get_time_ms() - phil->last_ate >= (unsigned long)phil->data->time_to_die) {
			philosopher_write(phil, "has died");
			printf("Because %lu >= %d\n", phil->last_ate - phil->data->starttime, phil->data->time_to_die);
			sem_post(phil->data->finished);
			return (0);
		}
		sem_post(phil->check);
		usleep(500);
	}
	return (0);
}

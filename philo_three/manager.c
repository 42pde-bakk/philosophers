/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:39:21 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/20 01:21:26 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	genocide(t_data *data)
{
	int i;

	i = 0;
	while (data->pids[i])
	{
		kill(data->pids[i], SIGTERM);
		printf("just killed %i, pid=%d\n", i, data->pids[i]);
		++i;
	}
	return ;
}

int	mr_manager(t_philo *philosophers, t_data *data)
{
	int		i;

	i = 0;
	while (1)
	{
		// if (get_time_ms() - philosophers[i].last_ate >=
		// 	(unsigned long)data->time_to_die) {
			if (0) {
			philosopher_write(&philosophers[i], "has died");
			genocide(data);
			return (1);
		}
		++i;
		if (i >= data->nb_phil)
			i = 0;
	}
	return (0);
}

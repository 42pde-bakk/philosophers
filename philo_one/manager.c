/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:39:21 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/17 20:51:29 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*kill_all_philosophers(t_philo *philosophers)
{
	
}

void	*start_managing(void *param)
{
	t_philo	*philosophers;
	int		i;

	philosophers = param;
	i = 0;
	while (1)
	{
		if (get_time_ms() - philosophers[i].last_ate > philosophers[i].time_to_die)
			return (philo)
		++i;
		if (i >= philosophers[i].nb_phil)
			i = 0;
	}
}

int	setup_manager(t_philo *philosophers, pthread_t manager)
{
	if (pthread_create(&manager, NULL, start_managing, philosophers))
		return (1);
}

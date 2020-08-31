/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:29:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/31 11:52:47 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_death(t_philo *phil)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&phil->data->state_mutex);
	if (phil->data->state == DEAD)
		ret = 1;
	pthread_mutex_unlock(&phil->data->state_mutex);
	return (ret);
}

void	set_state(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->state_mutex);
	if (phil->data->state == ALIVE)
		phil->data->state = DONE;
	pthread_mutex_unlock(&phil->data->state_mutex);
}

int		grab_forks(t_philo *phil)
{
	pthread_mutex_lock(phil->lfork_mutex);
	if (check_death(phil))
	{
		pthread_mutex_unlock(phil->lfork_mutex);
		return (1);
	}
	philosopher_write(phil, "has taken fork");
	pthread_mutex_lock(phil->rfork_mutex);
	if (check_death(phil))
	{
		pthread_mutex_unlock(phil->lfork_mutex);
		pthread_mutex_unlock(phil->rfork_mutex);
		return (1);
	}
	philosopher_write(phil, "has taken fork");
	return (0);
}

void	*start_philosopher(void *param)
{
	t_philo			*phil;
	int				eatcount;

	phil = param;
	eatcount = -1;
	philosopher_eat(phil, &eatcount);
	usleep((phil->id % 2) * 300);
	while (eatcount != phil->data->eat_times && check_death(phil) == 0)
	{
		philosopher_write(phil, "is thinking");
		if (grab_forks(phil))
			break ;
		philosopher_eat(phil, &eatcount);
		usleep(phil->data->time_to_eat * 1000);
		pthread_mutex_unlock(phil->lfork_mutex);
		pthread_mutex_unlock(phil->rfork_mutex);
		if (check_death(phil))
			break ;
		philosopher_write(phil, "is sleeping");
		usleep(phil->data->time_to_sleep * 1000);
	}
	set_state(phil);
	return (NULL);
}

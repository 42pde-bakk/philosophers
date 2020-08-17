/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:29:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/17 20:29:50 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_write(t_philo *phil, const char *s)
{
	pthread_mutex_lock(&phil->data->pen);
	ft_put_ul_fd(get_time_ms() - phil->data->starttime, 1);
	ft_putchar_fd('\t', 1);
	ft_put_ul_fd(phil->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(s, 1, 0);
	ft_putchar_fd('\n', 1);
	pthread_mutex_unlock(&phil->data->pen);
}

void	*philosopher_death(t_philo *phil)
{
	philosopher_write(phil, "has died");
	pthread_mutex_unlock(phil->lfork_mutex);
	pthread_mutex_unlock(phil->rfork_mutex);
	return (NULL);
}

void	*start_philosopher(void *param)
{
	t_philo			*phil;
	int				eatcount;

	phil = param;
	phil->last_ate = get_time_ms();
	// printf("started up philosopher nb %i\n", phil->id);
	eatcount = 0;
	while (eatcount != phil->data->eat_times)
	{
		philosopher_write(phil, "is thinking");
		pthread_mutex_lock(phil->lfork_mutex);
		philosopher_write(phil, "has taken fork");
		pthread_mutex_lock(phil->rfork_mutex);
		philosopher_write(phil, "has taken fork");
		if (get_time_ms() - phil->last_ate >= (unsigned long)phil->data->time_to_die)
			return (philosopher_death(phil));
		phil->last_ate = get_time_ms();
		philosopher_write(phil, "is eating");
		usleep(phil->data->time_to_eat * 1000);

		pthread_mutex_unlock(phil->lfork_mutex);
		pthread_mutex_unlock(phil->rfork_mutex);
		
		philosopher_write(phil, "is sleeping");
		usleep(phil->data->time_to_sleep * 1000);
		++eatcount;
	}
	return NULL;
}

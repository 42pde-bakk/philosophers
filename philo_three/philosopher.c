/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:29:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/20 01:47:03 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_write(t_philo *phil, const char *s)
{
	sem_wait(phil->data->pen);
	ft_put_ul_fd(get_time_ms() - phil->data->starttime, 1);
	ft_putchar_fd('\t', 1);
	ft_put_ul_fd(phil->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(s, 1, 0);
	ft_putchar_fd('\n', 1);
	sem_post(phil->data->pen);
}

void	*philosopher_death(t_philo *phil)
{
	philosopher_write(phil, "has died");
	sem_post(phil->myforks);
	sem_post(phil->myforks);
	phil->state = DEAD;
	return (NULL);
}

void	*start_philosopher(t_philo *phil)
{
	int				eatcount;

	phil->last_ate = get_time_ms();
	eatcount = 0;
	while (eatcount != phil->data->eat_times)
	{
		philosopher_write(phil, "is thinking");
		sem_wait(phil->myforks);
		philosopher_write(phil, "has taken fork");
		sem_wait(phil->myforks);
		philosopher_write(phil, "has taken fork");
		phil->last_ate = get_time_ms();
		philosopher_write(phil, "is eating");
		++eatcount;
		usleep(phil->data->time_to_eat * 1000);
		sem_post(phil->myforks);
		sem_post(phil->myforks);
		philosopher_write(phil, "is sleeping");
		usleep(phil->data->time_to_sleep * 1000);
	}
	phil->state = DONE;
	return NULL;
}

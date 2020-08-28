/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:29:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/28 19:01:53 by pde-bakk      ########   odam.nl         */
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

void	philosopher_eat(t_philo *phil, int *eatcount)
{
	sem_wait(phil->state_sem);
	phil->last_ate = get_time_ms();
	if (*eatcount != -1)
		philosopher_write(phil, "is eating");
	*eatcount += 1;
	sem_post(phil->state_sem);
}

void	start_philosopher(t_philo *phil)
{
	int	eatcount;

	eatcount = -1;
	philosopher_eat(phil, &eatcount);
	while (eatcount != phil->data->eat_times)
	{
		philosopher_write(phil, "is thinking");
		sem_wait(phil->data->forks);
		philosopher_write(phil, "has taken fork");
		sem_wait(phil->data->forks);
		philosopher_write(phil, "has taken fork");
		philosopher_eat(phil, &eatcount);
		usleep(phil->data->time_to_eat * 1000);
		sem_post(phil->data->forks);
		sem_post(phil->data->forks);
		philosopher_write(phil, "is sleeping");
		usleep(phil->data->time_to_sleep * 1000);
	}
	sem_post(phil->data->finished);
}

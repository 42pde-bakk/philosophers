/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:29:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/31 13:47:40 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_death(t_philo *phil)
{
	int	ret;

	ret = 0;
	sem_wait(phil->data->state_sem);
	if (phil->data->state == DEAD)
		ret = 1;
	sem_post(phil->data->state_sem);
	return (ret);
}

int		take_forks(t_philo *phil)
{
	sem_wait(phil->data->forks);
	if (check_death(phil))
	{
		sem_post(phil->data->forks);
		return (1);
	}
	philosopher_write(phil, "has taken fork");
	sem_wait(phil->data->forks);
	if (check_death(phil))
	{
		sem_post(phil->data->forks);
		sem_post(phil->data->forks);
		return (1);
	}
	philosopher_write(phil, "has taken fork");
	return (0);
}

void	philosopher_eat(t_philo *phil, int *eatcount)
{
	sem_wait(phil->data->state_sem);
	phil->last_ate = get_time_ms();
	if (*eatcount != -1)
		philosopher_write(phil, "is eating");
	*eatcount += 1;
	sem_post(phil->data->state_sem);
}

void	*start_philosopher(void *param)
{
	t_philo			*phil;
	int				eatcount;

	phil = param;
	usleep(phil->id % 2 * 200);
	eatcount = -1;
	philosopher_eat(phil, &eatcount);
	while (eatcount != phil->data->eat_times)
	{
		philosopher_write(phil, "is thinking");
		if (take_forks(phil))
			break ;
		philosopher_eat(phil, &eatcount);
		stupid_sleep(phil->data->time_to_eat);
		sem_post(phil->data->forks);
		sem_post(phil->data->forks);
		if (check_death(phil))
			break ;
		philosopher_write(phil, "is sleeping");
		stupid_sleep(phil->data->time_to_sleep);
		if (check_death(phil))
			break ;
	}
	return (set_state(phil));
}

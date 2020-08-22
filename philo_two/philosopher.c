/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 20:29:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/22 22:56:57 by peer          ########   odam.nl         */
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
	*eatcount += 1;
	sem_post(phil->data->state_sem);
}

void	*start_philosopher(void *param)
{
	t_philo			*phil;
	int				eatcount;

	phil = param;
	philosopher_eat(phil, &eatcount);
	eatcount = 0;
	while (eatcount != phil->data->eat_times)
	{
		philosopher_write(phil, "is thinking");
		if (take_forks(phil))
			break ;
		philosopher_eat(phil, &eatcount);
		philosopher_write(phil, "is eating");
		usleep(phil->data->time_to_eat * 1000);
		sem_post(phil->data->forks);
		sem_post(phil->data->forks);
		if (check_death(phil))
			break ;
		philosopher_write(phil, "is sleeping");
		usleep(phil->data->time_to_sleep * 1000);
		if (check_death(phil))
			break ;
	}
	return (NULL);
}

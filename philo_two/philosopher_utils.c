/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 18:10:36 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/23 18:15:34 by pde-bakk      ########   odam.nl         */
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

void	*set_state(t_philo *phil)
{
	sem_wait(phil->data->state_sem);
	if (phil->data->state == ALIVE)
		phil->data->state = DONE;
	sem_post(phil->data->state_sem);
	return (NULL);
}

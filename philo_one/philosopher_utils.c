/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/22 00:16:25 by peer          #+#    #+#                 */
/*   Updated: 2020/08/22 00:16:32 by peer          ########   odam.nl         */
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

void	set_eat_time(t_philo *phil)
{
	pthread_mutex_lock(&phil->last_ate_mutex);
	phil->last_ate = get_time_ms();
	pthread_mutex_unlock(&phil->last_ate_mutex);
}

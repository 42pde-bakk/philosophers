/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_struct.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 23:56:21 by peer          #+#    #+#                 */
/*   Updated: 2020/08/21 23:47:47 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_mutexes(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_phil)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		++i;
	}
	if (pthread_mutex_init(&data->pen, NULL))
		return (1);
	if (pthread_mutex_init(&data->state_mutex, NULL))
		return (1);
	return (0);
}

int		init_struct(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->nb_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->eat_times = -1;
	data->state = ALIVE;
	if (argc == 6)
		data->eat_times = ft_atoi(argv[5]);
	if (data->nb_phil <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
	|| data->time_to_sleep <= 0 || (argc == 6 && data->eat_times < 0))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_phil);
	if (!data->forks)
		return (1);
	if (init_mutexes(data))
	{
		free(data->forks);
		return (1);
	}
	data->starttime = get_time_ms();
	return (0);
}

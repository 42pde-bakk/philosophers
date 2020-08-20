/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_struct.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 23:56:21 by peer          #+#    #+#                 */
/*   Updated: 2020/08/21 01:04:41 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_mutexes(t_data *data)
{
	sem_unlink("/pen");
	data->pen = sem_open("/pen", O_CREAT, S_IRWXU | S_IRWXO, 1);
	if (data->pen == SEM_FAILED)
		return (1);
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU | S_IRWXO, data->nb_phil);
	if (data->forks == SEM_FAILED)
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
	if (argc == 6)
		data->eat_times = ft_atoi(argv[5]);
	if (data->nb_phil <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
	|| data->time_to_sleep <= 0 || (argc == 6 && data->eat_times < 0))
		return (1);
	if (init_mutexes(data))
		return (1);
	data->starttime = get_time_ms();
	return (0);
}

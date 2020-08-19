/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_struct.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 23:56:21 by peer          #+#    #+#                 */
/*   Updated: 2020/08/20 01:34:47 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_mutexes(t_data *data)
{
	data->pen = sem_open("/pen", O_CREAT, S_IRWXU | S_IRWXO, 1);
	if (data->pen == SEM_FAILED)
		return (1);	
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU | S_IRWXO, data->nb_phil);
	if (data->forks == SEM_FAILED)
		return (1);
	printf("we now have %s forks, nbphil = %d\n", data->forks->__size, data->nb_phil);
	return (0);
}

int		fill_data(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->nb_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->eat_times = -1;
	if (argc == 6)
		data->eat_times = ft_atoi(argv[5]);
	if (data->nb_phil <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 ||
	data->time_to_sleep <= 0 || (argc == 6 && data->eat_times < 0))
		return (1);
	if (init_mutexes(data))
		return (1);
	data->starttime = get_time_ms();
	data->pids = malloc(data->nb_phil * sizeof(int));
	if (!data->pids)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:49:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/20 01:47:58 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_philosopher(t_philo *philosopher, t_data *data, int i)
{
	memset(philosopher, 0, sizeof(t_philo));
	philosopher->id = i + 1;
	philosopher->data = data;
	philosopher->state = ALIVE;
	philosopher->last_ate = get_time_ms();
}

int		free_shit(t_philo *philosophers, int ret)
{
	free(philosophers);
	return (ret);
}

int		setup_threads(t_data *data)
{
	t_philo		*philosophers;
	int			i;
	int			pid;

	i = 0;
	philosophers = malloc(sizeof(t_philo) * data->nb_phil);
	if (!philosophers)
		return (1);
	// if (sem_close(data->forks)) {
	// 	printf("closing semaphore went wrong\n");
	// 	sem_unlink("/forks");
	// 	return (free_shit(philosophers, 1));
	// }
	
	while (i < data->nb_phil)
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		initialize_philosopher(&philosophers[i], data, i);
		if (pid == 0)
		{
			philosophers[i].myforks = 	data->forks = sem_open("/forks", O_CREAT, S_IRWXU | S_IRWXO, data->nb_phil);
			start_philosopher(&philosophers[i]);
			printf("philosopher %d done\n", i);
			exit(0);
		}
		data->pids[i] = pid;
		usleep(50);
		++i;
	}
	mr_manager(philosophers, data);
	i = 0;
	while (data->pids[i])
	{
		waitpid(data->pids[i], NULL, 0);
		++i;
	}
	return (free_shit(philosophers, 0));
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || fill_data(&data, argc, argv))
		return (ft_putstr_fd("bad arguments\n", 2, 1));
	if (setup_threads(&data))
		return (ft_putstr_fd("something went horribly wrong\n", 2, 1));
}

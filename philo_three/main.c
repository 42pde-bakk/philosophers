/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:49:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/28 17:56:38 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_philosopher(t_philo *philosopher, t_data *data, int i)
{
	memset(philosopher, 0, sizeof(t_philo));
	philosopher->id = i + 1;
	philosopher->data = data;
	philosopher->last_ate = get_time_ms();
	sem_unlink("/state_sem");
	philosopher->state_sem =
			sem_open("/state_sem", O_CREAT, S_IRWXU | S_IRWXO, 1);
}

int		free_shit(t_philo *philosophers, int ret)
{
	free(philosophers);
	return (ret);
}

void	fork_philosopher(t_philo philosopher)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, mr_manager, &philosopher))
		exit(1);
	pthread_detach(thread);
	start_philosopher(&philosopher);
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
	while (i < data->nb_phil)
	{
		initialize_philosopher(&philosophers[i], data, i);
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			fork_philosopher(philosophers[i]);
		data->pids[i] = pid;
		usleep(50);
		++i;
	}
	genocide(data);
	return (free_shit(philosophers, 0));
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || init_struct(&data, argc, argv))
		return (ft_putstr_fd("bad arguments\n", 2, 1));
	if (setup_threads(&data))
		return (ft_putstr_fd("something went horribly wrong\n", 2, 1));
	return (0);
}

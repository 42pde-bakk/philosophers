/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:49:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/19 23:56:58 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_philosopher(t_philo *philosopher, t_data *data, int i)
{
	memset(philosopher, 0, sizeof(t_philo));
	philosopher->id = i + 1;
	philosopher->data = data;
	philosopher->lfork_mutex = &data->forks[i];
	philosopher->rfork_mutex = &data->forks[(i + 1) % data->nb_phil];
	philosopher->state = ALIVE;
	philosopher->last_ate = get_time_ms();
}

int		free_shit(pthread_t *threads, t_philo *philosophers, int ret)
{
	free(threads);
	free(philosophers);
	return (ret);
}

int		setup_threads(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philosophers;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->nb_phil);
	if (!threads)
		return (1);
	philosophers = malloc(sizeof(t_philo) * data->nb_phil);
	if (!philosophers)
		return (1);
	while (i < data->nb_phil)
	{
		initialize_philosopher(&philosophers[i], data, i);
		if (pthread_create(&threads[i], NULL, start_philosopher, &philosophers[i]))
			return (free_shit(threads, philosophers, 1));
		if (pthread_detach(threads[i]))
			return (free_shit(threads, philosophers, 1));
		usleep(50);
		++i;
	}
	mr_manager(philosophers, data);
	return (free_shit(threads, philosophers, 0));
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || fill_data(&data, argc, argv))
		return (ft_putstr_fd("bad arguments\n", 2, 1));
	if (setup_threads(&data))
		return (ft_putstr_fd("something went horribly wrong\n", 2, 1));
	free(data.forks);
}

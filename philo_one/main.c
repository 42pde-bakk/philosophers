/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:49:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/19 00:48:06 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		fill_data(t_data *data, int argc, char **argv)
{
	int i;

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
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_phil);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_phil)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			free(data->forks);
			return (1);
		}
		++i;
	}
	if (pthread_mutex_init(&data->pen, NULL))
	{
		free(data->forks);
		return (1);
	}
	data->starttime = get_time_ms();
	free(data->forks);
	return (0);
}

void	initialize_philosopher(t_philo *philosopher, t_data *data, int i)
{
	memset(philosopher, 0, sizeof(t_philo));
	philosopher->id = i + 1;
	philosopher->data = data;
	philosopher->lfork = i;
	philosopher->lfork_mutex = &data->forks[philosopher->lfork];
	philosopher->rfork = (i + 1) % data->nb_phil;
	philosopher->rfork_mutex = &data->forks[philosopher->rfork];
	philosopher->state = ALIVE;
	philosopher->last_ate = get_time_ms();
	if (pthread_mutex_init(&philosopher->time_elapsed_mutex, NULL))
		exit(1);
}

int		free_shit(pthread_t *threads, t_philo *philosophers, int ret)
{
	free(threads);
	free(philosophers);
	return (ret);
}

int		setup_threads(t_data *data)
{
	int			i;
	pthread_t	*threads;
	t_philo		*philosophers;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->nb_phil);
	philosophers = malloc(sizeof(t_philo) * data->nb_phil);
	while (i < data->nb_phil)
	{
		if (i % 2 == 0)
		{
			initialize_philosopher(&philosophers[i], data, i);
			if (pthread_create(&threads[i], NULL, start_philosopher, &philosophers[i]))
				return (free_shit(threads, philosophers, 1));
			if (pthread_detach(threads[i]))
				return (free_shit(threads, philosophers, 1));
		}
		++i;
	}
	i = 0;
	usleep(500);
	while (i < data->nb_phil)
	{
		if (i % 2)
		{
			initialize_philosopher(&philosophers[i], data, i);
			if (pthread_create(&threads[i], NULL, start_philosopher, &philosophers[i]))
				return (free_shit(threads, philosophers, 1));
			if (pthread_detach(threads[i]))
				return (free_shit(threads, philosophers, 1));
		}
		++i;
	}
	mr_manager(philosophers, data);
	printf("mr manager is done\n");
	return (free_shit(threads, philosophers, 0));
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || fill_data(&data, argc, argv))
		return (ft_putstr_fd("bad arguments\n", 2, 1));
	setup_threads(&data);
	// system("leaks philo_one.out");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:49:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/17 20:48:14 by pde-bakk      ########   odam.nl         */
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
	philosopher->id = i + 1;
	philosopher->data = data;
	philosopher->lfork = i;
	philosopher->lfork_mutex = &data->forks[philosopher->lfork];
	philosopher->rfork = (i + 1) % data->nb_phil;
	philosopher->rfork_mutex = &data->forks[philosopher->rfork];
	philosopher->nb_phil = data->nb_phil;
}

int		free_shit(pthread_t *threads, t_philo *philosophers, int ret)
{
	free(threads);
	free(philosophers);
	return (ret);
}

int		start_threads(t_data *data)
{
	int			i;
	pthread_t	*threads;
	pthread_t	manager;
	t_philo		*philosophers;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->nb_phil);
	philosophers = malloc(sizeof(t_philo) * data->nb_phil);
	while (i < data->nb_phil)
	{
		initialize_philosopher(&philosophers[i], data, i);
		if (pthread_create(&threads[i], NULL, start_philosopher, &philosophers[i]))
			return (free_shit(threads, philosophers, 1));
		++i;
	}
	setup_manager(philosophers, &manager);
	i -= 1;
	while (i >= 0)
	{
		if (pthread_join(threads[i], NULL))
			return (free_shit(threads, philosophers, 1));
		--i;
	}
	return (free_shit(threads, philosophers, 0));
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || fill_data(&data, argc, argv))
		return (ft_putstr_fd("bad arguments\n", 2, 1));
	start_threads(&data);
	// system("leaks philo_one.out");
}

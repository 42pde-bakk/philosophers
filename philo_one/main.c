/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:49:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/26 16:20:22 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		initialize_philosopher(t_philo *philosopher, t_data *data, int i)
{
	memset(philosopher, 0, sizeof(t_philo));
	philosopher->id = i + 1;
	philosopher->data = data;
	philosopher->lfork_mutex = &data->forks[i];
	philosopher->rfork_mutex = &data->forks[(i + 1) % data->nb_phil];
	philosopher->last_ate = get_time_ms();
	if (pthread_mutex_init(&philosopher->last_ate_mutex, NULL))
		return (1);
	return (0);
}

int		setup_threads(t_data *data, t_philo *philosophers, pthread_t *threads)
{
	int			i;

	i = 0;
	while (i < data->nb_phil)
	{
		if (initialize_philosopher(&philosophers[i], data, i))
			return (1);
		if (pthread_create(&threads[i], NULL, start_philosopher,
			&philosophers[i]))
			return (1);
		++i;
	}
	mr_manager(philosophers, data);
	i = 0;
	while (i < data->nb_phil)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philosophers;
	pthread_t	*threads;

	if (argc < 5 || argc > 6 || init_struct(&data, argc, argv))
		return (ft_putstr_fd("bad arguments\n", 2, 1));
	philosophers = malloc(sizeof(t_philo) * data.nb_phil);
	if (!philosophers)
		return (ft_putstr_fd("cant malloc\n", 2, 1));
	threads = malloc(sizeof(pthread_t) * data.nb_phil);
	if (!threads)
		return (1);
	if (setup_threads(&data, philosophers, threads))
		return (ft_putstr_fd("something went horribly wrong\n", 2, 1));
	free(data.forks);
	free(philosophers);
	free(threads);
	return (0);
}

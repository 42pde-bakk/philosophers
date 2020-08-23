/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:49:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/23 18:26:21 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_philosopher(t_philo *philosopher, t_data *data, int i)
{
	memset(philosopher, 0, sizeof(t_philo));
	philosopher->id = i + 1;
	philosopher->data = data;
	philosopher->last_ate = get_time_ms();
}

int		free_shit(pthread_t *threads, t_philo *philosophers, int ret)
{
	free(threads);
	free(philosophers);
	return (ret);
}

void	join_threads(pthread_t *threads, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_phil)
	{
		if (pthread_join(threads[i], NULL))
			return ;
		++i;
	}
}

int		setup_threads(t_data *data)
{
	pthread_t	*threads;
	t_philo		*philos;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->nb_phil);
	if (!threads)
		return (1);
	philos = malloc(sizeof(t_philo) * data->nb_phil);
	if (!philos)
		return (1);
	while (i < data->nb_phil)
	{
		initialize_philosopher(&philos[i], data, i);
		if (pthread_create(&threads[i], NULL, start_philosopher, &philos[i]))
			return (free_shit(threads, philos, 1));
		++i;
	}
	mr_manager(philos, data);
	join_threads(threads, data);
	return (free_shit(threads, philos, 0));
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || init_struct(&data, argc, argv))
		return (ft_putstr_fd("bad arguments\n", 2, 1));
	if (setup_threads(&data))
		return (ft_putstr_fd("something went horribly wrong\n", 2, 1));
}

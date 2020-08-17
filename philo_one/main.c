/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:49:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/17 17:14:26 by pde-bakk      ########   odam.nl         */
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
			return (1);
		++i;
	}
	if (pthread_mutex_init(&data->pen, NULL))
		return (1);
	data->starttime = get_time_ms();
	return (0);
}

void	philosopher_write(t_philo *phil, const char *s)
{
	pthread_mutex_lock(&phil->data->pen);
	ft_put_ul_fd(get_time_ms() - phil->data->starttime, 1);
	ft_putchar_fd('\t', 1);
	ft_put_ul_fd(phil->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(s, 1, 0);
	ft_putchar_fd('\n', 1);
	pthread_mutex_unlock(&phil->data->pen);
}

void	*philosopher_death(t_philo *phil)
{
	philosopher_write(phil, "has died");
	pthread_mutex_unlock(phil->lfork_mutex);
	pthread_mutex_unlock(phil->rfork_mutex);
	free(phil);
	return (NULL);
}

void	*start_philosopher(void *param)
{
	t_philo			*phil;
	int				eatcount;
	unsigned long	tim;

	phil = param;
	tim = get_time_ms();
	// printf("started up philosopher nb %i\n", phil->id);
	eatcount = 0;
	while (eatcount != phil->data->eat_times)
	{
		philosopher_write(phil, "is thinking");
		pthread_mutex_lock(phil->lfork_mutex);
		philosopher_write(phil, "has taken fork");
		pthread_mutex_lock(phil->rfork_mutex);
		philosopher_write(phil, "has taken fork");
		if (get_time_ms() - tim >= (unsigned long)phil->data->time_to_die)
			return (philosopher_death(phil));
		philosopher_write(phil, "is eating");
		tim = get_time_ms();
		usleep(phil->data->time_to_eat * 1000);

		pthread_mutex_unlock(phil->lfork_mutex);
		pthread_mutex_unlock(phil->rfork_mutex);
		
		philosopher_write(phil, "is sleeping");
		usleep(phil->data->time_to_sleep * 1000);
		++eatcount;
	}
	free(phil);
	return NULL;
}

t_philo	*new_philosopher_struct(int count, t_data *data)
{
	t_philo	*out;

	out = malloc(sizeof(t_philo));
	memset(out, 0, sizeof(t_philo));
	out->id = count + 1;
	out->data = data;
	out->lfork = count;
	out->lfork_mutex = &data->forks[out->lfork];
	out->rfork = (count + 1) % data->nb_phil;
	out->rfork_mutex = &data->forks[out->rfork];
	return (out);
}

int		start_threads(t_data *data)
{
	int count;
	pthread_t	threads[data->nb_phil];
	t_philo		*phil;

	count = 0;
	while (count < data->nb_phil)
	{
		phil = new_philosopher_struct(count, data);
		if (pthread_create(&threads[count], NULL, start_philosopher, phil))
			exit(1);
		++count;
	}
	count -= 1;
	while (count >= 0)
	{
		if (pthread_join(threads[count], NULL))
			exit(1);
		--count;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || fill_data(&data, argc, argv))
		return (ft_putstr_fd("bad arguments\n", 2, 1));
	start_threads(&data);
	// system("leaks philo_one.out");
}

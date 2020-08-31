/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:39:45 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/31 13:45:19 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

enum	e_state
{
	ALIVE,
	DEAD,
	DONE
};

typedef struct	s_data
{
	int				nb_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	int				state;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	pen;
	unsigned long	starttime;
}				t_data;

typedef struct	s_philo
{
	int				id;
	unsigned long	last_ate;
	pthread_mutex_t	*lfork_mutex;
	pthread_mutex_t	*rfork_mutex;
	pthread_mutex_t	last_ate_mutex;
	t_data			*data;
}				t_philo;

int				init_struct(t_data *data, int argc, char **argv);

void			philosopher_write(t_philo *phil, const char *s);
void			*start_philosopher(void *param);

int				mr_manager(t_philo *philosophers, t_data *data);

/*
** philosopher_utils.c
*/
void			philosopher_write(t_philo *phil, const char *s);
void			*philosopher_death(t_philo *phil);
void			philosopher_eat(t_philo *phil, int *eatcount);

void			ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(const char *s, int fd, int ret);
int				ft_atoi(const char *str);
void			ft_put_ul_fd(unsigned long n, int fd);
unsigned long	get_time_ms(void);
unsigned long	get_time_us(void);
void			stupid_sleep(unsigned long time2sleep);

#endif

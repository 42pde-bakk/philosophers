/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:39:45 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/19 00:21:29 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //rm pls
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

enum	e_state
{
	ALIVE,
	DONE,
	DEAD
};

typedef struct	s_data
{
	int	nb_phil;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int eat_times;
	pthread_mutex_t	*forks;
	pthread_mutex_t	pen;
	unsigned long	starttime;
}				t_data;

typedef struct	s_philo
{
	int				id;
	unsigned long	last_ate;
	int				amount_ate;
	int				lfork;
	pthread_mutex_t	*lfork_mutex;
	int				rfork;
	pthread_mutex_t	*rfork_mutex;
	t_data			*data;
	pthread_mutex_t	time_elapsed_mutex;
	int				state;
}				t_philo;

void		philosopher_write(t_philo *phil, const char *s);
void		*start_philosopher(void *param);

int			mr_manager(t_philo *philosophers, t_data *data);

void		ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(const char *s, int fd, int ret);
int			ft_atoi(const char *str);
void		ft_put_ul_fd(unsigned long n, int fd);

unsigned long	get_time_ms(void);
unsigned long	get_time_us(void);
#endif

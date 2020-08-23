/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:39:45 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/23 18:19:17 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
#include <stdio.h> //rm

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
	sem_t			*forks;
	sem_t			*pen;
	sem_t			*state_sem;
	unsigned long	starttime;
}				t_data;

typedef struct	s_philo
{
	int				id;
	int				amount_ate;
	unsigned long	last_ate;
	t_data			*data;
}				t_philo;

int				init_struct(t_data *data, int argc, char **argv);

void			philosopher_write(t_philo *phil, const char *s);
void			*set_state(t_philo *phil);
void			*start_philosopher(void *param);

int				mr_manager(t_philo *philosophers, t_data *data);

void			ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(const char *s, int fd, int ret);
int				ft_atoi(const char *str);
void			ft_put_ul_fd(unsigned long n, int fd);

unsigned long	get_time_ms(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gettime.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/16 03:51:31 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/31 13:57:53 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

unsigned long	get_time_ms(void)
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

unsigned long	get_time_us(void)
{
	struct timeval	tv;
	unsigned long	out;

	gettimeofday(&tv, NULL);
	out = tv.tv_sec;
	out *= 1000 * 1000;
	out += tv.tv_usec;
	return (out);
}

void			stupid_sleep(unsigned long time2sleep)
{
	unsigned long	start;

	start = get_time_us();
	time2sleep *= 1000;
	while (get_time_us() - start < time2sleep)
		usleep(100);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gettime.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/16 03:51:31 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/16 03:55:36 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

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
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 * 1000;
	time += tv.tv_usec;
	return (time);	
}

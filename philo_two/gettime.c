/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gettime.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/16 03:51:31 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/21 01:05:21 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

unsigned long	get_time_ms(void)
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 21:52:46 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/08/21 00:50:53 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

int			ft_putstr_fd(const char *s, int fd, int ret)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
	return (ret);
}

static int	iswhitespace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
	{
		return (1);
	}
	return (0);
}

int			ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	result;

	result = 0;
	sign = 1;
	while (iswhitespace(*str))
		str++;
	if (*str == '-' || (*str < '0' && *str > '9'))
		return (-1);
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (10 * result) + (*str - '0');
		str++;
	}
	if (result > 9223372036854775807 && sign == -1)
		return (0);
	else if (result >= 9223372036854775807)
		return (-1);
	return (sign * result);
}

void		ft_put_ul_fd(unsigned long n, int fd)
{
	if (n >= 10)
	{
		ft_put_ul_fd(n / 10, fd);
		ft_put_ul_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

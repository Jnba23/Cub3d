/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:06:41 by asayad            #+#    #+#             */
/*   Updated: 2024/10/30 12:07:22 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

long	ft_atoi(char *str)
{
	int					sign;
	long				num;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		num = (num * 10) + (*str - 48);
		if (num > INT_MAX)
			return (num * sign);
		str++;
	}
	return (num * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (0);
	return (1);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
		write(2, &s[i++], 1);
	write(fd, "\n", 1);
}

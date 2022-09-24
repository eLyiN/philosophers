/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:57:38 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/24 10:06:19 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signo;
	int	nbr;

	i = 0;
	signo = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signo = -1;
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 10 + (str[i++] - '0');
		else
			return (-1);
	}
	return (signo * nbr);
}

void	error_code(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(STDOUT_FILENO, "Error\n", 7);
	write(STDOUT_FILENO, str, i);
	write(STDOUT_FILENO, "\n", 1);
}

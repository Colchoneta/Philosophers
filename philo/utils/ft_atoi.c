/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:58:21 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/04 18:58:22 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_char_in_string(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (str[i] == c);
}

static int	ft_pos_char_in_string(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	const char	*base;
	int			sign;
	int			res;
	int			i;

	base = "0123456789";
	sign = 1;
	res = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && ft_char_in_string(base, str[i]))
	{
		res *= 10;
		res += ft_pos_char_in_string(base, str[i]);
		i++;
	}
	return (res * sign);
}

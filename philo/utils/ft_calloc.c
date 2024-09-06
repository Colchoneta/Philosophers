/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:47:42 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/04 18:58:31 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_bzero(void *s, size_t n)
{
	memset(s, '\0', n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(size * count);
	if (!result)
		return (0);
	ft_bzero(result, size * count);
	return (result);
}

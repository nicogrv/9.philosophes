/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:18:24 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/05 15:33:47 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

long long	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec + tv.tv_sec * 1000000);
}

int	ft_usleep(t_philo *philo, int time)
{
	long long	tmp;

	if (philo->deadstop == 1)
		return (1);
	tmp = ft_get_time();
	while (ft_get_time() < (tmp + time))
		usleep(50);
	if (philo->deadstop == 1)
		return (1);
	return (0);
}

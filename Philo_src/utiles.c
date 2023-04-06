/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:18:24 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/06 12:03:14 by ngriveau         ###   ########.fr       */
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

	
	pthread_mutex_lock(&philo->endmutex);
	if (philo->deadstop == 1)
		return (pthread_mutex_unlock(&philo->endmutex), 1);
	pthread_mutex_unlock(&philo->endmutex);
	tmp = ft_get_time();
	while (ft_get_time() < (tmp + time))
		usleep(50);
	pthread_mutex_lock(&philo->endmutex);
	if (philo->deadstop == 1)
		return (pthread_mutex_unlock(&philo->endmutex), 1);
	pthread_mutex_unlock(&philo->endmutex);
	return (0);
}

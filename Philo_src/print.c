/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:30:44 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/30 16:42:28 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

void ft_print_info(t_philo *philo, t_human *human)
{
	gettimeofday(&philo->tv, NULL);
	if (human->status == EAT)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[33;1m%ld\t%d is eating\e[0m\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);

	}
	else if (human->status == SLEEP)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[35;1m%ld\t%d is sleeping\e[0m\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else if (human->status == THINK)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[32;1m%ld\t%d is thinking\e[0m\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[31;1m%ld\t%d ERROR\e[0m\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	} 
	

}


void ft_print_take_fork(t_philo *philo, t_human *human, int side)
{
	gettimeofday(&philo->tv, NULL);
	if (side == 0)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[34;1m%ld\t%d has taken a fork\e[0m\n", ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else if (side == 1)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[34;1m%ld\t%d has taken a fork\e[0m\n", ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[31;1m%ld\t%d ERROR FORK\e[0m\n", ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
		
}
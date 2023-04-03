/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:30:44 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/03 14:27:28 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

void ft_print_info(t_philo *philo, t_human *human)
{
	gettimeofday(&philo->tv, NULL);
	if (human->status == EAT)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("%lld\t"BOLD"%d"YELLOW" is eating"NC"\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);

	}
	else if (human->status == SLEEP)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("%lld\t"BOLD"%d"LIGHTPURPLE" is sleeping"NC"\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else if (human->status == THINK)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("%lld\t"BOLD"%d"LIGHTBLUE" is thinking"NC"\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[31;1m%lld\t%d ERROR\e[0m\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	} 
	

}


void ft_print_take_fork(t_philo *philo, t_human *human, int side)
{
	gettimeofday(&philo->tv, NULL);
	if (side == 0)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("%lld\t"BOLD"%d"LIGHTBLUE" has taken a fork"NC"\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else if (side == 1)
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("%lld\t"BOLD"%d"LIGHTBLUE" has taken a fork"NC"\n",ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else
	{
		pthread_mutex_lock(&philo->printmutex);
		printf("\e[31;1m%lld\t%d ERROR FORK\e[0m\n", ft_get_time() - philo->av.time, human->nb);
		pthread_mutex_unlock(&philo->printmutex);
	}
		
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:30:44 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/05 15:33:09 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

void	ft_print_info_thinks(t_philo *philo, t_human *human)
{
	pthread_mutex_lock(&philo->printmutex);
	pthread_mutex_lock(&philo->endmutex);
	if (philo->deadstop == 0)
		printf("%lld\t"BOLD" %d "LIGHTBLUE" is thinking"NC"\n", \
			(ft_get_time() - philo->av.time) / 1000, human->nb);
	pthread_mutex_unlock(&philo->endmutex);
	pthread_mutex_unlock(&philo->printmutex);
}

void	ft_print_info(t_philo *philo, t_human *human)
{
	if (human->status == EAT)
	{
		pthread_mutex_lock(&philo->printmutex);
		pthread_mutex_lock(&philo->endmutex);
		if (philo->deadstop == 0)
			printf("%lld\t"BOLD" %d "YELLOW" is eating"NC"\n", (ft_get_time() - \
				philo->av.time) / 1000, human->nb);
		pthread_mutex_unlock(&philo->endmutex);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else if (human->status == SLEEP)
	{
		pthread_mutex_lock(&philo->printmutex);
		pthread_mutex_lock(&philo->endmutex);
		if (philo->deadstop == 0)
			printf("%lld\t"BOLD" %d "LIGHTPURPLE" is sleeping"NC"\n", \
				(ft_get_time() - philo->av.time) / 1000, human->nb);
		pthread_mutex_unlock(&philo->endmutex);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else if (human->status == THINK)
		ft_print_info_thinks(philo, human);
}

void	ft_print_take_fork(t_philo *philo, t_human *human, int side)
{
	// enelver le side
	if (side == 0)
	{
		pthread_mutex_lock(&philo->printmutex);
		pthread_mutex_lock(&philo->endmutex);
		if (philo->deadstop == 0)
			printf("%lld\t"BOLD" %d "LIGHTBLUE" has taken a fork"NC"\n", \
				(ft_get_time() - philo->av.time) / 1000, human->nb);
		else
			pthread_mutex_unlock(human->leftmutex);
		pthread_mutex_unlock(&philo->endmutex);
		pthread_mutex_unlock(&philo->printmutex);
	}
	else if (side == 1)
	{
		pthread_mutex_lock(&philo->printmutex);
		pthread_mutex_lock(&philo->endmutex);
		if (philo->deadstop == 0)
			printf("%lld\t"BOLD" %d "LIGHTBLUE" has taken a fork"NC"\n", \
				(ft_get_time() - philo->av.time) / 1000, human->nb);
		else
			pthread_mutex_unlock(human->rightmutex);
		pthread_mutex_unlock(&philo->endmutex);
		pthread_mutex_unlock(&philo->printmutex);
	}
}

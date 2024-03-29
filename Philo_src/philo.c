/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:19:54 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/12 12:26:49 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

int	ft_philo_suit(t_human *human, t_philo *philo)
{
	human->status = EAT;
	ft_print_info(philo, human);
	pthread_mutex_lock(&human->mutex_timing);
	human->nb_eat += 1;
	human->timing = ft_get_time();
	if (philo->av.nbr_eat <= human->nb_eat)
		return (ft_unlock_mutex_id(human), \
			pthread_mutex_unlock(&human->mutex_timing), 1);
	pthread_mutex_unlock(&human->mutex_timing);
	if (ft_usleep(philo, philo->av.eat))
		return (ft_unlock_mutex_id(human), 1);
	ft_unlock_mutex_id(human);
	if (human->nb_eat == philo->av.nbr_eat)
		return (1);
	human->status = SLEEP;
	ft_print_info(philo, human);
	if (ft_usleep(philo, philo->av.sleep))
		return (1);
	human->status = THINK;
	ft_print_info(philo, human);
	if (philo->av.nbr_philo % 2 != 0 && ft_usleep(philo, (philo->av.die \
		- philo->av.eat - philo->av.sleep) / 2))
		return (1);
	return (0);
}

void	ft_philo_death(t_human *human, t_philo *philo)
{
	pthread_mutex_lock(&philo->printmutex);
	if (philo->deadstop == 0)
		printf("\e[31;1m""%lld %d died\e[0m\n", (ft_get_time() - \
philo->av.time) / 1000, human->nb);
	pthread_mutex_lock(&philo->endmutex);
	philo->deadstop = 1;
	pthread_mutex_unlock(&philo->endmutex);
	pthread_mutex_unlock(&philo->printmutex);
	return ;
}

void	*ft_philo(void *av)
{
	t_philo	*philo;
	t_human	*human;

	human = (t_human *)av;
	philo = (t_philo *) human->philo;
	while (ft_get_time() < human->start)
		usleep(50);
	pthread_mutex_lock(&human->mutex_timing);
	human->timing = ft_get_time();
	pthread_mutex_unlock(&human->mutex_timing);
	if (human->nb % 2 == 1)
		usleep(100);
	while (1)
	{
		ft_lock_mutex_id(philo, human);
		if (ft_philo_suit(human, philo))
			return (NULL);
	}
	return (NULL);
}

void	*ft_one_philo_bis(void *av)
{
	t_philo	*philo;

	philo = (t_philo *) av;
	philo->av.time = ft_get_time();
	printf("0"BOLD" 1 "LIGHTBLUE"has taken a fork"NC"\n");
	ft_usleep(philo, philo->av.die);
	printf("\e[31;1m%d 1 died"NC"\n", philo->av.die / 1000);
	return (NULL);
}

void	ft_one_philo(t_philo *philo)
{
	pthread_t	idthread;

	pthread_create(&idthread, NULL, ft_one_philo_bis, philo);
	pthread_join(idthread, NULL);
	return (ft_free_all(philo, 0));
}

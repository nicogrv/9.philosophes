/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:18:00 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/06 11:04:41 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

void	ft_create_fork(t_philo *philo)
{
	int	i;

	philo->av.mutex = malloc(sizeof(pthread_mutex_t) * philo->av.nbr_philo);
	philo->av.fork = malloc(sizeof(int) * (philo->av.nbr_philo + 1));
	philo->av.fork[philo->av.nbr_philo] = -42;
	i = -1;
	while (++i < philo->av.nbr_philo)
	{
		pthread_mutex_init(&philo->av.mutex[i], NULL);
		philo->av.fork[i] = 0;
	}
	return ;
}

void	ft_create_philo_2(t_philo *philo, t_human *tmp, int i)
{
	if (i == philo->av.nbr_philo)
	{
		tmp->rightfork = &philo->av.fork[0];
		tmp->rightmutex = &philo->av.mutex[0];
	}
	else
	{
		tmp->rightfork = &philo->av.fork[i];
		tmp->rightmutex = &philo->av.mutex[i];
	}
	tmp->next = NULL;
}

void	ft_create_philo(t_philo *philo)
{
	int		i;
	t_human	*tmp;

	i = 1;
	tmp = &philo->human;
	while (i <= philo->av.nbr_philo)
	{
		tmp->next = malloc(sizeof(t_human));
		if (tmp->next == NULL)
			return ;
		tmp = tmp->next;
		tmp->philo = (void *) philo;
		tmp->nb = i;
		tmp->timing = philo->av.time + 500;
		tmp->nb_eat = 0;
		tmp->status = THINK;
		tmp->timing = philo->tv.tv_usec;
		tmp->leftfork = &philo->av.fork[i - 1];
		tmp->leftmutex = &philo->av.mutex[i - 1];
		ft_create_philo_2(philo, tmp, i);
		i++;
	}
	tmp->next = NULL;
}

void	ft_init(t_philo *philo)
{
	gettimeofday(&philo->tv, NULL);
	philo->deadstop = 0;
	philo->human.nb = -42;
	philo->human.status = -42;
	philo->human.timing = -42;
	philo->human.leftfork = NULL;
	philo->human.rightfork = NULL;
	philo->av.time = ft_get_time();
	pthread_mutex_init(&philo->printmutex, NULL);
	pthread_mutex_init(&philo->endmutex, NULL);
	ft_create_fork(philo);
	ft_create_philo(philo);
}

int	ft_parsing(int c, char **av, t_philo *philo)
{
	int	i;

	i = 1;
	if (c != 5 && c != 6)
		return (printf(LIGHTRED"Error input (5 or 6 argument)\n"NC));
	while (av[i])
	{
		if (ft_verifint(av[i]) == -1)
			return (printf(LIGHTRED"Error input (0 < NUMBER < 2.147.483.648)\n"\
				NC));
		i++;
	}
	philo->av.nbr_philo = ft_atoi(av[1]);
	philo->av.die = ft_atoi(av[2]) * 1000;
	philo->av.eat = ft_atoi(av[3]) * 1000;
	philo->av.sleep = ft_atoi(av[4]) * 1000;
	if (c == 6)
		philo->av.nbr_eat = ft_atoi(av[5]);
	else
		philo->av.nbr_eat = 2147483647;
	return (0);
}

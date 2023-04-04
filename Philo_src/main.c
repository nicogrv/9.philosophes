/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:18:24 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/04 15:08:12 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"


void ft_create_fork(t_philo *philo)
{
	int i;

	philo->av.mutex = malloc(sizeof(pthread_mutex_t) * philo->av.nbr_philo);
	philo->av.fork = malloc(sizeof(int) * (philo->av.nbr_philo + 1));
	philo->av.fork[philo->av.nbr_philo] = -42;
	i = -1;
	while(++i < philo->av.nbr_philo)
	{
		pthread_mutex_init(&philo->av.mutex[i], NULL);
		philo->av.fork[i] = 0;
	}
	return ;
}


void ft_create_philo(t_philo *philo)
{
	int i;
	t_human *tmp;

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
		tmp->nb_eat = 0;
		tmp->status = THINK;
		tmp->timing = philo->tv.tv_usec;
		tmp->leftfork = &philo->av.fork[i - 1];
		tmp->leftmutex = &philo->av.mutex[i - 1];
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
		i++;
	}
}


void ft_init(t_philo *philo)
{
	gettimeofday(&philo->tv, NULL);
	philo->deadstop = 0;
	philo->av.nbr_philo = 4;
	philo->av.nbr_eat = 100;
	philo->av.die = 410*1000;
	philo->av.eat = 200*1000;
	philo->av.sleep = 200*1000;
	philo->human.nb = -42;
	philo->human.status = -42;
	philo->human.timing = -42;
	philo->human.leftfork = NULL;
	philo->human.rightfork = NULL;
	pthread_mutex_init(&philo->printmutex, NULL);
	pthread_mutex_init(&philo->startmutex, NULL);
	pthread_mutex_init(&philo->endmutex, NULL);
	ft_create_fork(philo);
	ft_create_philo(philo);
}
long long ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec + tv.tv_sec*1000000);
}

void ft_lock_mutex_id(t_philo *philo, t_human *human)
{
	// printf("%lld\tn`%d lock\n", ft_get_time() - philo->av.time, human->nb);
	if (human->nb % 2 == 0)
	{
		
		pthread_mutex_lock(human->leftmutex);
		ft_print_take_fork(philo, human, 0);
		pthread_mutex_lock(human->rightmutex);
		ft_print_take_fork(philo, human, 1);
	}
	else
	{
		pthread_mutex_lock(human->rightmutex);
		ft_print_take_fork(philo, human, 1);
		pthread_mutex_lock(human->leftmutex);
		ft_print_take_fork(philo, human, 0);
	}
	return ;
}

void ft_unlock_mutex_id(t_human *human)
{
	if (human->nb % 2 == 0)
	{
		pthread_mutex_unlock(human->leftmutex);
		pthread_mutex_unlock(human->rightmutex);
	}
	else
	{
		pthread_mutex_unlock(human->rightmutex);
		pthread_mutex_unlock(human->leftmutex);
	}
	return ;
}



int ft_usleep(t_philo *philo, int time)
{
	long long tmp;
	if (philo->deadstop == 1)
		return (1);
	tmp = ft_get_time();
	// printf("\n%lld\ttime%lld\n",ft_get_time() - philo->av.time, tmp + time - philo->av.time);
	while (ft_get_time() < (tmp + time))
		usleep(50);
	if (philo->deadstop == 1)
		return (1);
	return (0);
}
void *ft_philo(void *av)
{
	t_philo *philo;
	t_human *human;
	
	human = (t_human *)av;
	philo = (t_philo *) human->philo;
	human->timing = ft_get_time();
	pthread_mutex_lock(&philo->startmutex);
	pthread_mutex_unlock(&philo->startmutex);
	while (1)
	{
		ft_lock_mutex_id(philo, human);
		if ((ft_get_time() - human->timing) >= philo->av.die)
		{
			ft_unlock_mutex_id(human);
			pthread_mutex_lock(&philo->printmutex);
			if (philo->deadstop == 0)
				printf("\e[31;1m""%lld(%lld)\t%d died\e[0m\n", (ft_get_time() - philo->av.time)/1000, (ft_get_time() - human->timing)/1000, human->nb);
			pthread_mutex_lock(&philo->endmutex);
			philo->deadstop = 1;
			pthread_mutex_unlock(&philo->endmutex);
			pthread_mutex_unlock(&philo->printmutex);
			ft_unlock_mutex_id(human);
			return NULL;
		}
		human->status = EAT;
		human->nb_eat += 1;
		ft_print_info(philo, human);
		human->timing = ft_get_time();
		// printf("human->nb_eat == %d\t philo->av.nbr_eat = %d\n", human->nb_eat, philo->av.nbr_eat);
		if (philo->av.nbr_eat <= human->nb_eat || ft_usleep(philo, philo->av.eat))
			return (ft_unlock_mutex_id(human), NULL);
		ft_unlock_mutex_id(human);
		if (human->nb_eat == philo->av.nbr_eat)
			return NULL;
		human->status = SLEEP;
		ft_print_info(philo, human);
		if (ft_usleep(philo, philo->av.sleep))
			return NULL;
		human->status = THINK;
		ft_print_info(philo, human);
	}
    return NULL;
}

int main(int c, char **av)
{
	t_philo		philo;
	pthread_t	*idthread;
	t_human		*tmp;
	int			i;
    
	(void) c;
    (void) av;
	ft_init(&philo);
	tmp = philo.human.next;
	i = 0;
	idthread = malloc(sizeof(pthread_t) * philo.av.nbr_philo);
	pthread_mutex_lock(&philo.startmutex);
	while (tmp)
	{
		pthread_create(&idthread[i], NULL, ft_philo, tmp);
		tmp = tmp->next;
		i++;
	}
	philo.av.time = ft_get_time();
	pthread_mutex_unlock(&philo.startmutex);
	tmp = philo.human.next;
	i = 0;
	usleep(1000);
	while (i < philo.av.nbr_philo)
	{
		// printf("Attente de la fin du philo %d\n", i+1);
        pthread_join(idthread[i], NULL);
        // printf("phlo %d terminé\n", i+1);
		i++;
	}
    return(0);
}

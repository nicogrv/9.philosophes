/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:18:24 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/29 18:29:55 by ngriveau         ###   ########.fr       */
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
		tmp->nb = i;
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
	philo->av.time = philo->tv.tv_usec/1000 + philo->tv.tv_sec*1000;
	philo->av.nbr_philo = 10;
	philo->av.die = 0;
	philo->av.eat = 500;
	philo->av.sleep = 962;
	philo->human.nb = -42;
	philo->human.status = -42;
	philo->human.timing = -42;
	philo->human.leftfork = NULL;
	philo->human.rightfork = NULL;
	ft_create_fork(philo);
	ft_create_philo(philo);
}
long ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec/1000 + tv.tv_sec*1000);
}


void ft_print_info(t_philo *philo, t_human *human)
{
	gettimeofday(&philo->tv, NULL);
	if (human->status == EAT)
		printf("\e[33;1m%ld\t%d eating\e[0m\n",ft_get_time() - philo->av.time, human->nb);
	else if (human->status == SLEEP)
		printf("\e[35;1m%ld\t%d sleeping\e[0m\n",ft_get_time() - philo->av.time, human->nb);
	else if (human->status == THINK)
		printf("\e[32;1m%ld\t%d thinking\e[0m\n",ft_get_time() - philo->av.time, human->nb);
	else 
		printf("\e[31;1m%ld\t%d ERROR\e[0m\n",ft_get_time() - philo->av.time, human->nb);
	

}


void ft_print_take_fork(t_philo *philo, t_human *human, int side)
{
	gettimeofday(&philo->tv, NULL);
	if (side == 0)
		printf("\e[34;1m%ld\t%d take LeftFork\e[0m\n", ft_get_time() - philo->av.time, human->nb);
	else if (side == 1)
		printf("\e[34;1m%ld\t%d take RightFork\e[0m\n", ft_get_time() - philo->av.time, human->nb);
	else
		printf("\e[31;1m%ld\t%d ERROR side\e[0m\n", ft_get_time() - philo->av.time, human->nb);
		
}



void *ft_philo(void *av)
{
	t_philo *philo;
	t_human *human;
	int id;
	
	philo = (t_philo *)av;
	id = philo->tmpid + 1;
	philo->tmpid = -1;
	human = &philo->human;
	while (0 < id)
	{
		human = human->next;
		id--;
	}
	while (1)
	{
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
		if (*human->leftfork == 0 && *human->rightfork == 0)
		{
			// fprintf(stderr, "dans le if\n\n");
			
			*human->leftfork = human->nb;
			*human->rightfork = human->nb;
			if (human->nb == *human->leftfork && human->nb == *human->rightfork)
			{
				human->status = EAT;
				ft_print_info(philo, human);
				usleep(philo->av.eat);
				gettimeofday(&philo->tv, NULL);
				human->timing = philo->tv.tv_usec/1000 + philo->tv.tv_sec*1000;
				*human->leftfork = 0;
				*human->rightfork = 0;
			}
		}
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
		human->status = SLEEP;
		ft_print_info(philo, human);
		usleep(philo->av.sleep);
		human->status = THINK;
		ft_print_info(philo, human);
		usleep(philo->av.sleep);
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
	// ft_get_time(&philo);
	tmp = philo.human.next;
	i = 0;
	idthread = malloc(sizeof(pthread_t) * philo.av.nbr_philo);
	while (tmp)
	{
		philo.tmpid = i;
		pthread_create(&idthread[i], NULL, ft_philo, &philo);
		while (0 <= philo.tmpid)
			(void) i;
		usleep(100);
		tmp = tmp->next;
		i++;
	}
	tmp = philo.human.next;
	// while (1)
	// {
	// 	if ()
	// }
	// pthread_join(my_thread, NULL);
	// pthread_join(my_thread2, NULL);
	// fprintf(stderr, "value = %d\n", philo.value);
	while (1)
		(void) i;
    return(0);
}

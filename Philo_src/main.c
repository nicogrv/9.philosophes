/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:18:24 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/29 13:59:33 by ngriveau         ###   ########.fr       */
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
		tmp->leftfork = philo->av.fork[i - 1];
		tmp->leftmutex = &philo->av.mutex[i - 1];
		if (i == philo->av.nbr_philo)
		{
			tmp->rightfork = philo->av.fork[0];
			tmp->rightmutex = &philo->av.mutex[0];	
		}
		else
		{
			tmp->rightfork = philo->av.fork[i];
			tmp->rightmutex = &philo->av.mutex[i];
		}
		tmp->next = NULL;
		i++;
	}
}


void ft_init(t_philo *philo)
{
	gettimeofday(&philo->tv, &philo->tz);
	philo->av.nbr_philo = 4;
	philo->av.die = 0;
	philo->av.eat = 0;
	philo->av.sleep = 0;
	philo->human.nb = -42;
	philo->human.status = -42;
	philo->human.timing = -42;
	philo->human.leftfork = -42;
	philo->human.rightfork = -42;
	ft_create_fork(philo);
	ft_create_philo(philo);
}


void ft_print_info(t_human *human)
{
	if (human->status == EAT)
		printf("\e[33mPhilo n'%d eat\e[0m\n", human->nb);
	else if (human->status == SLEEP)
		printf("\e[35mPhilo n'%d sleep\e[0m\n", human->nb);
	else if (human->status == THINK)
		printf("\e[36mPhilo n'%d think\e[0m\n", human->nb);
	else 
		printf("\e[36mPhilo n'%d ERROR\e[0m\n", human->nb);
	

}


void ft_print_time(t_philo *philo, char *text)
{
	gettimeofday(&philo->tv, &philo->tz);
    printf(".%s\t%ld \n", text, philo->tv.tv_usec);
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
	pthread_mutex_lock(human->leftmutex);
	pthread_mutex_lock(human->rightmutex);
	// fprintf(stderr, "if %d\tforkLeft = %d\tforkRight = %d\n", human->nb, human->leftfork, human->rightfork);
	if (human->leftfork == 0 && human->rightfork == 0)
	{
		// fprintf(stderr, "if %d\tforkLeft = %d\tforkRight = %d\n", human->nb, human->leftfork, human->rightfork);
		human->leftfork = human->nb;
		human->rightfork = human->nb;
	pthread_mutex_unlock(human->leftmutex);
	pthread_mutex_unlock(human->rightmutex);
	if (human->nb == human->leftfork && human->nb == human->rightfork)
		human->status = EAT;
		// human->leftfork = 0;
		// human->rightfork = 0;
	}
	// fprintf(stderr, "philo %d\tforkLeft = %p\tforkRight = %p\n", human->nb, human->leftmutex, human->rightmutex);
	// fprintf(stderr, "philo 1\tforkLeft = %d\tforkRight = %d\n", philo->human.next->leftfork, philo->human.next->rightfork);
	ft_print_info(human);
	
	
	// gettimeofday(&philo->tv, &philo->tz);
	// while (philo->tv.tv_usec < 999000)
	// 	gettimeofday(&philo->tv, &philo->tz);

	// ft_print_time(philo, "start");
	// while (!philo->value)
	// {
	// 	pthread_mutex_lock(&philo->mutex);
	// 	philo->value = 1;
	// 	if (philo->value == 1)
	// 	{
	// 		ft_print_time(philo, "sort");
	// 		while (i < 100000000)
	// 			 i++;
	// 		pthread_mutex_unlock(&philo->mutex);
	// 		return NULL;
	// 	}
    return NULL;
}



int main(int c, char **av)
{
	t_philo philo;
	pthread_t idthread[4];
	t_human *tmp;
	int i;
	int f;
    
	(void) c;
    (void) av;
	ft_init(&philo);

	tmp = philo.human.next;
	i = 0;
	while (tmp)
	{
		philo.tmpid = i;
		pthread_create(&idthread[i], NULL, ft_philo, &philo);
		while (0 <= philo.tmpid)
			(void) i;
		for (f = 0; f < 300000000; f++)
			(void) f;
		fprintf(stderr, "main %d\tforkLeft = %d\tforkRight = %d\n", tmp->nb, tmp->leftfork, tmp->rightfork);
		
		tmp = tmp->next;
		fprintf(stderr, "main %d\tforkLeft = %d\tforkRight = %d\n", tmp->nb, tmp->leftfork, tmp->rightfork);
		i++;
	}
	while (1)
		(void) c;
	// pthread_join(my_thread, NULL);
	// pthread_join(my_thread2, NULL);
	// fprintf(stderr, "value = %d\n", philo.value);

    return(0);
}
	
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:18:24 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/28 19:30:19 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./_Include/philo.h"



void ft_create_fork(t_philo *philo)
{
	int i;


	philo->av.fork = malloc(sizeof(int) * philo->av.nbr_philo + 1);
	philo->av.fork[philo->av.nbr_philo] = -42;
	i = -1;
	while(philo->av.fork[++i] != -42)
		philo->av.fork[i] = 0;
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
		if (i == philo->av.nbr_philo)
			tmp->rightfork = philo->av.fork[0];
		else
			tmp->rightfork = philo->av.fork[i];
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
	if (human->status == SLEEP)
		printf("\e[35mPhilo n'%d sleep\e[0m\n", human->nb);
	if (human->status == THINK)
		printf("\e[36mPhilo n'%d think\e[0m\n", human->nb);

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
	// fprintf(stderr, "philo %d\tforkLeft = %d\tforkRight = %d\n", human->nb, human->leftfork, human->rightfork);
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
		tmp = tmp->next;
		i++;
	}

	// pthread_join(my_thread, NULL);
	// pthread_join(my_thread2, NULL);
	// fprintf(stderr, "value = %d\n", philo.value);

    return(0);
}
	
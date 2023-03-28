/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:18:24 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/28 17:35:25 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./_Include/philo.h"

void ft_print_time(t_philo *philo, char *text)
{
	gettimeofday(&philo->tv, &philo->tz);
    printf(".%s\t%ld \n", text, philo->tv.tv_usec);
}

void *ft_philo(void *av)
{
	t_philo *philo;
	int i = 0;
	
	philo = (t_philo *)av;
	gettimeofday(&philo->tv, &philo->tz);
	while (philo->tv.tv_usec < 999000)
		gettimeofday(&philo->tv, &philo->tz);

	ft_print_time(philo, "start");
	while (!philo->value)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->value = 1;
		if (philo->value == 1)
		{
			ft_print_time(philo, "sort");
			while (i < 100000000)
				 i++;
			pthread_mutex_unlock(&philo->mutex);
			return NULL;
		}
	}
    return NULL;
}
int main(int c, char **av)
{
	t_philo philo;
	pthread_t my_thread;
	pthread_t my_thread2;
    
	(void) c;
    (void) av;
	
	philo.value = 0;
	gettimeofday(&philo.tv, &philo.tz);
	pthread_create(&my_thread, NULL, ft_philo, &philo);
	pthread_create(&my_thread2, NULL, ft_philo, &philo);
	pthread_join(my_thread, NULL);
	pthread_join(my_thread2, NULL);
	fprintf(stderr, "value = %d\n", philo.value);
    return(0);
}
	
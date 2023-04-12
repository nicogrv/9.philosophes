/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:18:24 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/12 12:14:42 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

void	ft_lock_mutex_id(t_philo *philo, t_human *human)
{
	if (human->nb % 2 == 0)
	{
		pthread_mutex_lock(human->leftmutex);
		ft_print_take_fork(philo, human);
		pthread_mutex_lock(human->rightmutex);
		ft_print_take_fork(philo, human);
	}
	else
	{
		pthread_mutex_lock(human->rightmutex);
		ft_print_take_fork(philo, human);
		pthread_mutex_lock(human->leftmutex);
		ft_print_take_fork(philo, human);
	}
	return ;
}

void	ft_unlock_mutex_id(t_human *human)
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

void	main_death(t_philo *philo, t_human *human)
{
	while (1)
	{
		pthread_mutex_lock(&human->mutex_timing);
		if (philo->av.nbr_eat <= human->nb_eat)
			philo->nb_of_eat++;
		else if ((ft_get_time() - human->timing) / 1000 * 1000 >= \
			philo->av.die / 1000 * 1000)
		{
			pthread_mutex_unlock(&human->mutex_timing);
			ft_philo_death(human, philo);
			break ;
		}
		pthread_mutex_unlock(&human->mutex_timing);
		if (philo->nb_of_eat == philo->av.nbr_philo)
			break ;
		if (human->next == NULL)
		{
			philo->nb_of_eat = 0;
			human = &philo->human;
		}
		human = human->next;
		usleep(50);
	}
}

void	main_end(t_philo *philo)
{
	int		i;
	t_human	*human;

	human = philo->human.next;
	while (ft_get_time() < philo->av.time + 500)
		usleep(50);
	main_death(philo, human);
	i = -1;
	while (++i < philo->av.nbr_philo)
		pthread_join(philo->idthread[i], NULL);
	ft_free_all(philo, 1);
}

int	main(int c, char **av)
{
	t_philo		philo;
	t_human		*tmp;
	int			i;

	if (ft_parsing(c, av, &philo))
		return (printf(ORANGE"Number_of_philosophers | Time_to_die | Time_to_ea\
t | Time_to_sleep | (Number_of_times_each_philosopher_must_eat)"NC"\n\n"));
	if (ft_init(&philo))
		return (1);
	if (philo.av.nbr_philo == 1)
		return (ft_one_philo(&philo), 1);
	tmp = philo.human.next;
	i = 0;
	philo.idthread = malloc(sizeof(pthread_t) * philo.av.nbr_philo);
	if (philo.idthread == NULL)
		return (ft_free_all(&philo, 0), 1);
	while (tmp)
	{
		pthread_create(&philo.idthread[i], NULL, ft_philo, tmp);
		tmp = tmp->next;
		i++;
	}
	return (main_end(&philo), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:30:44 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/12 12:11:31 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

void	ft_free_all(t_philo *philo, int id)
{
	t_human	*tmp;
	t_human	*adresse;

	tmp = philo->human.next;
	while (tmp)
	{
		adresse = tmp->next;
		free(tmp);
		tmp = adresse;
	}
	if (id == 1)
		free(philo->idthread);
	free(philo->av.fork);
	free(philo->av.mutex);
}

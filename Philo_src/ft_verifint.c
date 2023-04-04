/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:19:54 by ngriveau          #+#    #+#             */
/*   Updated: 2023/04/04 15:25:57 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/philo.h"

int	ft_verifint_pt2(char *str, int i, long nb, int signe)
{
	int	index;

	index = i;
	while ('0' <= str[i] && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	if ((i - index) > 15)
		return (-1);
	if (str[i] == '\0' && 1 <= (nb * signe)
		&& (nb * signe) <= 2147483647 && (i - index) < 15)
		return (0);
	return (-1);
}

int	ft_verifint(char *str)
{	
	int		i;
	int		signe;
	long	nb;

	signe = 1;
	i = 0;
	nb = 0;
	if (!str[i])
		return (-1);
	while (('\t' <= str[i] && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		i++;
		signe = -signe;
	}
	if (str[i] == '\0')
		return (-1);
	return (ft_verifint_pt2(str, i, nb, signe));
}
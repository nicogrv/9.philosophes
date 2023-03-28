/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:05:10 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/28 19:30:14 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# define EAT 4
# define SLEEP 10
# define THINK 12

typedef struct s_human
{
	int				nb;
	int				status;
	int				timing;
	int				leftfork;
	int				rightfork;
	struct s_human	*next;
}				t_human;

typedef struct s_init
{
	int		nbr_philo;
	int		die;
	int		eat;
	int		sleep;
	int		*fork;
}				t_init;

typedef struct s_philo
{
	t_init			av;
	t_human			human;
	struct timeval	tv;
    struct timezone	tz;
	int				tmpid;
	pthread_mutex_t mutex;
}				t_philo;


#endif

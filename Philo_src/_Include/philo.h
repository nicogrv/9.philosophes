/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:05:10 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/30 14:32:37 by ngriveau         ###   ########.fr       */
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
	long			timing;
	int				*leftfork;
	pthread_mutex_t	*leftmutex;
	int				*rightfork;
	pthread_mutex_t	*rightmutex;
	struct s_human	*next;
}				t_human;

typedef struct s_init
{
	int				nbr_philo;
	int				die;
	int				eat;
	int				sleep;
	int				*fork;
	long			time;
	pthread_mutex_t *mutex;
}				t_init;

typedef struct s_philo
{
	t_init			av;
	t_human			human;
	struct timeval	tv;
	int				tmpid;
	pthread_mutex_t printmutex;
	int				deadstop;
	
}				t_philo;



//Print
void	ft_print_info(t_philo *philo, t_human *human);
void	ft_print_take_fork(t_philo *philo, t_human *human, int side);

//main
void ft_create_fork(t_philo *philo);
void ft_create_philo(t_philo *philo);
void ft_init(t_philo *philo);
long ft_get_time(void);
void ft_lock_mutex_id(t_philo *philo, t_human *human);
void ft_unlock_mutex_id(t_human *human);
int ft_usleep(t_philo *philo, int time);
void *ft_philo(void *av);
int main(int c, char **av);


#endif

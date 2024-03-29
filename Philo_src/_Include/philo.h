/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:05:10 by pbizien           #+#    #+#             */
/*   Updated: 2023/04/12 12:09:30 by ngriveau         ###   ########.fr       */
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

# define BOLD "\e[1m"

# define NC "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define ORANGE "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define LIGHTGRAY "\033[0;37m"

# define DARKGRAY "\033[1;30m"
# define LIGHTRED "\033[1;31m"
# define LIGHTGREEN "\033[1;32m"
# define LIGHTBLUE "\033[1;34m"
# define LIGHTPURPLE "\033[1;35m"
# define LIGHTCYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"

typedef struct s_human
{
	int				nb;
	int				nb_eat;
	int				status;
	long long		timing;
	pthread_mutex_t	mutex_timing;
	long long		start;
	int				*leftfork;
	pthread_mutex_t	*leftmutex;
	int				*rightfork;
	pthread_mutex_t	*rightmutex;
	struct s_human	*next;
	void			*philo;
}				t_human;

typedef struct s_init
{
	int				nbr_philo;
	int				nbr_philo_eat;
	int				nbr_eat;
	int				die;
	int				eat;
	int				sleep;
	int				*fork;
	long long		time;
	pthread_mutex_t	*mutex;
}				t_init;

typedef struct s_philo
{
	int				nb_of_eat;
	t_init			av;
	t_human			human;
	struct timeval	tv;
	pthread_mutex_t	printmutex;
	pthread_mutex_t	endmutex;
	pthread_t		*idthread;
	int				deadstop;
}				t_philo;

//Print
void		ft_print_info(t_philo *philo, t_human *human);
void		ft_print_take_fork(t_philo *philo, t_human *human);

//main
int			ft_create_fork(t_philo *philo);
int			ft_create_philo(t_philo *philo);
int			ft_init(t_philo *philo);
void		ft_lock_mutex_id(t_philo *philo, t_human *human);
void		ft_unlock_mutex_id(t_human *human);
int			ft_usleep(t_philo *philo, int time);
int			main(int c, char **av);

//Philo
void		ft_one_philo(t_philo *philo);
void		ft_philo_death(t_human *human, t_philo *philo);
void		*ft_philo(void *av);

//Parsing
int			ft_verifint(char *str);
int			ft_parsing(int c, char **av, t_philo *philo);
int			ft_atoi(const char *str);

//Free
void		ft_free_all(t_philo *philo, int id);

//Utiles
long long	ft_get_time(void);
int			ft_usleep(t_philo *philo, int time);

#endif

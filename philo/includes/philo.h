/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:46:12 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/23 11:32:40 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

/*_____________ Structures _______________________*/

typedef struct s_args
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	write_mutex;
}t_args;

typedef enum s_status
{
	THINKING,
	EATING,
	SLEEPING,
	DONE,
	DEAD,
}t_status;

typedef struct s_philo
{
	int					id;
	long long			init_time;
	pthread_t			thread;
	long long			meal_time;
	pthread_mutex_t		meal_mutex;
	int					meal_count;
	int					fork_disp;
	int					fork_nbr;
	pthread_mutex_t		fork_mutex;
	struct s_philo		*next_philo;
	pthread_mutex_t		status_mutex;
	t_status			status;
	t_args				*args;
}t_philo;

/*_____________ Functions _______________________*/

//actions.c

void		leave_forks(t_philo *philo);
void		eating_process(t_philo *philo);
void		sleeping_process(t_philo *philo);
void		take_forks(t_philo *philo);
void		thinking_process(t_philo *philo);

//init.c

void		thread_init(t_philo **philo, t_args *args);
void		philo_init(t_philo **philo, t_args *args);

//main.c

int			error_return(char *message, t_philo **philo, t_args *args);
void		quit_program(t_philo **philo, t_args *args);
int			parse_args(int argc, char **argv, t_philo **philo, t_args *args);

//process.c

int			end_check(t_philo **philo, t_args *args);
void		death_check(t_philo **philo, t_args *args);
void		*philo_routine(void *philo);
void		one_philo(t_philo **philo);
void		philo_process(t_philo **philo, t_args *args);

//tools.c

void		better_sleep(int duration, t_philo *philo);
void		print_actions(int time, char *action, t_philo *philo);
long long	get_time(void);
int			ft_atoi(const char *str);

#endif
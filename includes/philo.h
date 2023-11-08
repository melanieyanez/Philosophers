/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:46:12 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/08 15:10:24 by myanez-p         ###   ########.fr       */
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
	int		nb_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_meals;
}t_args;

typedef struct s_philo
{
	int					id;
	long long			init_time;
	int					is_dead;
	pthread_t			thread;
	int					meal_time;
	int					meal_count;
	t_args				*args;
}t_philo;

/*_____________ Functions _______________________*/

//actions.c

void		*eating_process(t_philo *philo);
void		*sleeping_process(t_philo *philo);
void		*thinking_process(t_philo *philo);

//main.c

void		parse_args(int argc, char **argv, t_args *args);

//init.c

long long	get_time(void);
void		philo_init(t_philo **philo, t_args *args);

//ft_atoi.c

int			ft_atoi(const char *str);

//process.c

void		*death_check(t_philo **philo, t_args *args);
void		*philo_routine(void *philo);
void		philo_create(t_philo **philo, t_args *args);
void		philo_process(t_philo **philo, t_args *args);

#endif
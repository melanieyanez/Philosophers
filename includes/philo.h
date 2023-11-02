/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:46:12 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/02 17:22:48 by myanez-p         ###   ########.fr       */
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
	pthread_t			thread;
	int					meal_time;
	int					meal_count;
	t_args				*args;
}t_philo;

/*_____________ Functions _______________________*/

//main.c

void	parse_args(int argc, char **argv, t_args *args);

//init.c

void	init_args(t_args *args);

//ft_atoi.c

int		ft_atoi(const char *str);

void	philo_init(t_philo **philo, t_args *args);
long long	get_time(void);

#endif
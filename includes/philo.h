/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:46:12 by myanez-p          #+#    #+#             */
/*   Updated: 2023/10/30 17:21:00 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>

/*_____________ Structures _______________________*/

typedef struct s_args
{
	int		nb_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_meals;
}t_args;

/*_____________ Functions _______________________*/

//main.c

void	parse_args(int argc, char **argv);

//init.c

void	init_args(t_args *args);

//ft_atoi.c

int	ft_atoi(const char *str);

#endif
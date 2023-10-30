/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:05:45 by myanez-p          #+#    #+#             */
/*   Updated: 2023/10/30 16:54:15 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_args(t_args *args)
{
	args->nb_philos = -1;
	args->time_to_die = -1;
	args->time_to_eat = -1;
	args->time_to_sleep = -1;
	args->nb_meals = INT_MAX;
}

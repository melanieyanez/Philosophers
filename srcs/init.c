/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:05:45 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/12 20:34:43 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thread_init(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		//if (i % 2)
			//usleep(5000);
		pthread_create(&(philo[i]->thread), NULL, philo_routine, (philo[i]));
		i ++;
	}
}

void	philo_init(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		philo[i]->id = i;
		philo[i]->init_time = get_time();
		philo[i]->meal_time = get_time();
		philo[i]->meal_count = 0;
		philo[i]->goal = 0;
		philo[i]->fork_disp = 1;
		philo[i]->fork_nbr = 0;
		pthread_mutex_init(&(philo[i]->fork_mutex), NULL);
		philo[i]->next_philo = philo[(i + 1) % args->nb_philos];
		philo[i]->status = THINKING;
		philo[i]->args = args;
		i ++;
	}
	thread_init(philo, args);
}

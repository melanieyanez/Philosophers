/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:05:45 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/22 13:17:27 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thread_init(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		pthread_create(&(philo[i]->thread), NULL, philo_routine, (philo[i]));
		i += 2;
	}
	usleep(5000);
	i = 1;
	while (i < args->nb_philos)
	{
		pthread_create(&(philo[i]->thread), NULL, philo_routine, (philo[i]));
		i += 2;
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
		philo[i]->fork_disp = 1;
		philo[i]->fork_nbr = 0;
		pthread_mutex_init(&(philo[i]->fork_mutex), NULL);
		pthread_mutex_init(&(philo[i]->status_mutex), NULL);
		pthread_mutex_init(&(philo[i]->meal_mutex), NULL);
		philo[i]->next_philo = philo[(i + 1) % args->nb_philos];
		philo[i]->status = THINKING;
		philo[i]->args = args;
		i ++;
	}
}

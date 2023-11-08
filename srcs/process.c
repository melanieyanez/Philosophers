/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:47 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/08 15:56:12 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_check(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (42)
	{
		while (i < args->nb_philos)
		{
			if ((get_time() - philo[i]->meal_time)
				> philo[i]->args->time_to_die)
			{
				printf("philo %d is dead\n", philo[i]->id + 1);
				exit(0);
			}
			i ++;
		}
		return (NULL);
	}
}

void	*philo_routine(void *philo)
{
	//printf("philo %d started\n", ((t_philo *) philo)->id + 1);
	while (((t_philo *) philo)->meal_count < ((t_philo *) philo)->args->nb_meals)
	{
		eating_process((t_philo *) philo);
		sleeping_process((t_philo *) philo);
	}
	return (NULL);
}

// penser a init 0 et 2 et 4 en meme temps
// puis a init 1 et 3 et 5 etc.
// sleep necessaire?

void	philo_create(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		//printf("philo %d created\n", i + 1);
		pthread_create(&(philo[i]->thread), NULL, philo_routine, (philo[i]));
		i ++;
	}
}

void	philo_process(t_philo **philo, t_args *args)
{
	int	i;

	philo_init(philo, args);
	philo_create(philo, args);
	death_check(philo, args);
	i = 0;
	while (i < args->nb_philos)
	{
		pthread_join(philo[i]->thread, NULL);
		i ++;
	}
}

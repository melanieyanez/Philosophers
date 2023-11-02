/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:05:45 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/02 17:23:04 by myanez-p         ###   ########.fr       */
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

void	*eating_process(t_philo *philo)
{
	(void) philo;
	printf("philo %d is eating\n", philo->id);
	//usleep(philo->args->time_to_eat * 1000);
	printf("philo %d is done eating\n", philo->id);
	philo->args->nb_meals += 1;
	philo->meal_time = get_time() - philo->init_time;
	return (NULL);
}

void	*sleeping_process(t_philo *philo)
{
	(void) philo;
	printf("philo %d is sleeping\n", philo->id);
	//usleep(philo->args->time_to_sleep * 1000);
	printf("philo %d is done sleeping\n", philo->id);
	return (NULL);
}

void	*dying_process(t_philo *philo)
{
	if (get_time() - philo->meal_time > philo->args->time_to_die)
	{
		printf("philo %d is dying\n", philo->id);
		exit(0);
	}
	return (NULL);
}

void	*philo_routine(void *philo)
{
	(void) philo;
	//printf("philo %d started\n", ((t_philo *) philo)->id);
	eating_process((t_philo *) philo);
	sleeping_process((t_philo *) philo);
	return (NULL);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

// penser a init 0 et 2 et 4 en meme temps
// puis a init 1 et 3 et 5 etc.
// sleep necessaire?

void	philo_init(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		pthread_create(&(philo[i]->thread), NULL, philo_routine, (philo[i]));
		philo[i]->init_time = get_time();
		philo[i]->args = args;
		//printf("%lld\n", philo[i]->init_time);
		printf("philo %d created\n", i);
		//usleep(5);
		i ++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:47 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/12 11:49:57 by melanieyane      ###   ########.fr       */
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

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!philo->args->stop)
	{
		while (philo->meal_count < philo->args->nb_meals)
		{
			//death_check()
			if (philo->status == THINKING)
			{
				thinking_process(philo);
			}
			else if (philo->status == EATING)
			{
				eating_process(philo);
			}
			else if (philo->status == SLEEPING)
			{
				sleeping_process(philo);
			}
		}
	}
	return (NULL);
}
// checker si on a besoin pour un seul philo

void	philo_process(t_philo **philo, t_args *args)
{
	pthread_mutex_init(&args->stop_mutex, NULL);
	philo_init(philo, args);
}

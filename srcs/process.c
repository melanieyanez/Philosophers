/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:47 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/12 20:28:45 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	death_check(t_philo *philo)
{
	if ((get_time() - philo->meal_time) > philo->args->time_to_die)
	{
		if (!philo->args->stop)
			printf("philo %d is dead\n", philo->id + 1);
		pthread_mutex_lock(&(philo->args->stop_mutex));
		philo->args->stop = 1;
		pthread_mutex_unlock(&(philo->args->stop_mutex));
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
			death_check(philo);
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

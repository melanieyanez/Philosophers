/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:47 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/16 16:37:50 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TO DO
//un seul philo
//ameliorer end_check pour quitter quand ils ont tous assez mangé
//remplacer les exit par des return qui quitte le programme
//faire une fonction qui free tout
//attention! quand ils ont tous mangé, ca continue quand meme

#include "../includes/philo.h"

int	end_check(t_philo **philo)
{
	int	i;

	i = 0;
	while (42)
	{
		if (i == philo[i]->args->nb_philos - 1)
		{
			if (philo[i]->status != DONE)
				i = 0;
			else
			{
				pthread_mutex_lock(&(philo[i]->args->stop_mutex));
				philo[i]->args->stop = 1;
				pthread_mutex_unlock(&(philo[i]->args->stop_mutex));
				return (1);
			}
		}
		i ++;
	}
}

int	death_check(t_philo **philo)
{
	int	i;

	i = 0;
	while (42)
	{
		if (i == philo[i]->args->nb_philos - 1)
			i = 0;
		if (get_time() - philo[i]->meal_time > philo[i]->args->time_to_die)
		{
			philo[i]->status = DEAD;
			print_actions(get_time() - philo[i]->init_time, "is dead", philo[i]);
			pthread_mutex_lock(&(philo[i]->args->stop_mutex));
			philo[i]->args->stop = 1;
			pthread_mutex_unlock(&(philo[i]->args->stop_mutex));
			return (1);
		}
		i ++;
	}
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!philo->args->stop)
	{
		while (philo->meal_count <= philo->args->nb_meals  && !philo->args->stop)
		{
			if (philo->status == THINKING && !philo->args->stop)
			{
				thinking_process(philo);
			}
			else if (philo->status == EATING && !philo->args->stop)
			{
				eating_process(philo);
			}
			else if (philo->status == SLEEPING && !philo->args->stop)
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
	//if (death_check(philo))
		//exit(0);
	if (end_check(philo))
		exit (0);
	//if (end_check(philo) || death_check(philo))
		//exit(0) ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:47 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/17 17:45:13 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TO DO
//un seul philo
//remplacer les exit par des return qui quitte le programme
//faire une fonction qui free tout
//ajouter protection malloc

#include "../includes/philo.h"

int	end_check(t_philo **philo, t_args *args)
{
	int	i;
	int	all_done;

	i = 0;
	all_done = 0;
	while (i < args->nb_philos)
	{
		if (philo[i]->status == DONE)
			all_done ++;
		i ++;
	}
	if (all_done == args->nb_philos)
		return (1);
	return (0);
}

void	death_check(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (!end_check(philo, args))
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
			break ;
		}
		i ++;
	}
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!philo->args->stop && philo->status != DONE)
	{
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
	return (NULL);
}

// checker si on a besoin pour un seul philo

void	philo_process(t_philo **philo, t_args *args)
{
	int	i;

	pthread_mutex_init(&args->stop_mutex, NULL);
	philo_init(philo, args);
	death_check(philo, args);
	i = 0;
	while (i < args->nb_philos)
	{
		pthread_join(philo[i]->thread, NULL);
		i ++;
	}
	quit_program(philo, args);
}

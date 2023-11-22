/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:47 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/22 16:24:44 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	end_check(t_philo **philo, t_args *args)
{
	int	i;
	int	all_done;

	i = 0;
	all_done = 0;
	while (i < args->nb_philos)
	{
		pthread_mutex_lock(&(philo[i]->status_mutex));
		if (philo[i]->status == DONE)
			all_done ++;
		pthread_mutex_unlock(&(philo[i]->status_mutex));
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
		pthread_mutex_lock(&(philo[i]->meal_mutex));
		if (get_time() - philo[i]->meal_time > philo[i]->args->time_to_die)
		{	
			pthread_mutex_unlock(&(philo[i]->meal_mutex));
			pthread_mutex_lock(&(philo[i]->status_mutex));
			philo[i]->status = DEAD;
			pthread_mutex_unlock(&(philo[i]->status_mutex));
			print_actions(get_time() - philo[i]->init_time, "died", philo[i]);
			pthread_mutex_lock(&(philo[i]->args->stop_mutex));
			philo[i]->args->stop = 1;
			pthread_mutex_unlock(&(philo[i]->args->stop_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo[i]->meal_mutex));
		i ++;
	}
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!philo->args->stop && philo->status != DONE)
	{
		pthread_mutex_lock(&(philo->status_mutex));
		if (philo->status == THINKING)
		{
			pthread_mutex_unlock(&(philo->status_mutex));
			thinking_process(philo);
		}
		else if (philo->status == EATING)
		{
			pthread_mutex_unlock(&(philo->status_mutex));
			eating_process(philo);
		}
		else if (philo->status == SLEEPING)
		{
			pthread_mutex_unlock(&(philo->status_mutex));
			sleeping_process(philo);
		}
		else
			pthread_mutex_unlock(&(philo->status_mutex));
	}
	return (NULL);
}

void	one_philo(t_philo **philo)
{
	pthread_mutex_lock(&(philo[0]->fork_mutex));
	print_actions(get_time() - philo[0]->init_time, "is thinking", philo[0]);
	print_actions(get_time() - philo[0]->init_time, \
		"has taken a fork", philo[0]);
	better_sleep(philo[0]->args->time_to_die, philo[0]);
	print_actions(get_time() - philo[0]->init_time, "is dead", philo[0]);
	pthread_mutex_unlock(&(philo[0]->fork_mutex));
}

void	philo_process(t_philo **philo, t_args *args)
{
	int	i;

	pthread_mutex_init(&args->stop_mutex, NULL);
	pthread_mutex_init(&args->write_mutex, NULL);
	philo_init(philo, args);
	if (args->nb_philos == 1)
		one_philo(philo);
	else
	{
		thread_init(philo, args);
		death_check(philo, args);
		i = 0;
		while (i < args->nb_philos)
		{
			pthread_join(philo[i]->thread, NULL);
			i ++;
		}
	}
	quit_program(philo, args);
}

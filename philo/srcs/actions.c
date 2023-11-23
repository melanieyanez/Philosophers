/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:57 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/23 11:56:32 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*----------------------------------------------*/
/*  Releases the forks of the current philosopher and his neighbor. */

void	leave_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->stop_mutex));
	if (philo->args->stop)
	{
		pthread_mutex_unlock(&(philo->args->stop_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->args->stop_mutex));
	pthread_mutex_lock(&(philo->fork_mutex));
	philo->fork_disp = 1;
	pthread_mutex_unlock(&(philo->fork_mutex));
	philo->fork_nbr = 1;
	pthread_mutex_lock(&(philo->next_philo->fork_mutex));
	philo->next_philo->fork_disp = 1;
	pthread_mutex_unlock(&(philo->next_philo->fork_mutex));
	philo->fork_nbr = 0;
}

/*----------------------------------------------*/
/* Eating process for the philosopher, */
/* including waiting, printing, and fork release. */

void	eating_process(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->stop_mutex));
	if (philo->args->stop)
	{
		pthread_mutex_unlock(&(philo->args->stop_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->args->stop_mutex));
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->meal_time = get_time();
	pthread_mutex_unlock(&(philo->meal_mutex));
	print_actions(get_time() - philo->init_time, "is eating", philo);
	better_sleep(philo->args->time_to_eat, philo);
	leave_forks(philo);
	philo->meal_count += 1;
	pthread_mutex_lock(&(philo->status_mutex));
	if (philo->meal_count == philo->args->nb_meals)
		philo->status = DONE;
	else
		philo->status = SLEEPING;
	pthread_mutex_unlock(&(philo->status_mutex));
}

/*----------------------------------------------*/
/* Sleeping process for the philosopher, */
/* including printing and waiting for a specified duration. */

void	sleeping_process(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->stop_mutex));
	if (philo->args->stop)
	{
		pthread_mutex_unlock(&(philo->args->stop_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->args->stop_mutex));
	print_actions(get_time() - philo->init_time, "is sleeping", philo);
	better_sleep(philo->args->time_to_sleep, philo);
	pthread_mutex_lock(&(philo->status_mutex));
	philo->status = THINKING;
	pthread_mutex_unlock(&(philo->status_mutex));
}

/*----------------------------------------------*/
/* Takes available forks for the current philosopher. */

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->stop_mutex));
	if (philo->args->stop)
	{
		pthread_mutex_unlock(&(philo->args->stop_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->args->stop_mutex));
	pthread_mutex_lock(&(philo->fork_mutex));
	if (philo->fork_disp)
	{
		print_actions(get_time() - philo->init_time, "has taken a fork", philo);
		philo->fork_disp = 0;
		philo->fork_nbr += 1;
	}
	pthread_mutex_unlock(&(philo->fork_mutex));
	pthread_mutex_lock(&(philo->next_philo->fork_mutex));
	if (philo->next_philo->fork_disp)
	{
		print_actions(get_time() - philo->init_time, "has taken a fork", philo);
		philo->next_philo->fork_disp = 0;
		philo->fork_nbr += 1;
	}
	pthread_mutex_unlock(&(philo->next_philo->fork_mutex));
}

/*----------------------------------------------*/
/* Thinking process for the philosopher, */
/* including printing and acquiring the necessary forks.*/

void	thinking_process(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->stop_mutex));
	if (philo->args->stop)
	{
		pthread_mutex_unlock(&(philo->args->stop_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->args->stop_mutex));
	print_actions(get_time() - philo->init_time, "is thinking", philo);
	pthread_mutex_lock(&(philo->args->stop_mutex));
	while (!philo->args->stop && philo->fork_nbr < 2)
	{
		pthread_mutex_unlock(&(philo->args->stop_mutex));
		take_forks(philo);
		pthread_mutex_lock(&(philo->args->stop_mutex));
	}
	pthread_mutex_unlock(&(philo->args->stop_mutex));
	pthread_mutex_lock(&(philo->status_mutex));
	philo->status = EATING;
	pthread_mutex_unlock(&(philo->status_mutex));
}

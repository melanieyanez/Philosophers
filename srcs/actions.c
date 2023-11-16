/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:57 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/16 16:33:10 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	leave_forks(t_philo *philo)
{
	if (philo->args->stop)
		return ;
	pthread_mutex_lock(&(philo->fork_mutex));
	philo->fork_disp = 1;
	pthread_mutex_unlock(&(philo->fork_mutex));
	pthread_mutex_lock(&(philo->next_philo->fork_mutex));
	philo->next_philo->fork_disp = 1;
	pthread_mutex_unlock(&(philo->next_philo->fork_mutex));
	philo->fork_nbr = 0;
}

void	eating_process(t_philo *philo)
{
	if (philo->args->stop)
		return ;
	philo->meal_time = get_time() - philo->init_time;
	print_actions(get_time() - philo->init_time, "is eating", philo);
	better_sleep(philo->args->time_to_eat, philo);
	philo->meal_count += 1;
	if (philo->args->nb_meals == philo->meal_count)
		philo->status = DONE;
	leave_forks(philo);
	philo->status = SLEEPING;
}

void	sleeping_process(t_philo *philo)
{
	if (philo->args->stop)
		return ;
	print_actions(get_time() - philo->init_time, "is sleeping", philo);
	better_sleep(philo->args->time_to_sleep, philo);
	philo->status = THINKING;
}

void	take_forks(t_philo *philo)
{
	if (philo->args->stop)
		return ;
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

void	thinking_process(t_philo *philo)
{
	if (philo->args->stop)
		return ;
	print_actions(get_time() - philo->init_time, "is thinking", philo);
	while (!philo->args->stop && philo->fork_nbr < 2)
	{
		take_forks(philo);
	}
	philo->status = EATING;
}

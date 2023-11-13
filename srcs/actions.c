/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:57 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/13 20:59:33 by melanieyane      ###   ########.fr       */
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
	print_actions(get_time(), "is eating", philo);
	while (!philo->args->stop && (get_time() < philo->meal_time + philo->args->time_to_eat))
		death_check(philo);
	philo->args->nb_meals += 1;
	philo->meal_time = get_time() - philo->init_time;
	leave_forks(philo);
	philo->status = SLEEPING;
}

void	sleeping_process(t_philo *philo)
{
	int	start;
	
	if (philo->args->stop)
		return ;
	start = get_time();
	print_actions(get_time(), "is sleeping", philo);
	while (!philo->args->stop && (get_time() < start + philo->args->time_to_sleep))
		death_check(philo);
	philo->status = THINKING;
}

void	take_forks(t_philo *philo)
{
	if (philo->args->stop)
		return ;
	pthread_mutex_lock(&(philo->fork_mutex));
	if (philo->fork_disp)
	{
		print_actions(get_time(), "has taken a fork", philo);
		philo->fork_disp = 0;
		philo->fork_nbr += 1;
	}
	pthread_mutex_unlock(&(philo->fork_mutex));
	pthread_mutex_lock(&(philo->next_philo->fork_mutex));
	if (philo->next_philo->fork_disp)
	{
		print_actions(get_time(), "has taken a fork", philo);
		philo->next_philo->fork_disp = 0;
		philo->fork_nbr += 1;
	}
	pthread_mutex_unlock(&(philo->next_philo->fork_mutex));
}

void	thinking_process(t_philo *philo)
{
	if (philo->args->stop)
		return ;
	print_actions(get_time(), "is thinking", philo);
	while (!philo->args->stop && philo->fork_nbr < 2)
	{
		death_check(philo);
		take_forks(philo);
	}
	philo->status = EATING;
}

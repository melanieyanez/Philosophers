/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:57 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/08 15:55:45 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//on cree le philo
//si il peut manger, il mange
//si il peut pas manger, il pense
//une fois qu'il a mangé, il dort
//et rebolotte

void	*eating_process(t_philo *philo)
{
	printf("philo %d is eating\n", philo->id + 1);
	//usleep(philo->args->time_to_eat * 1000);
	//printf("philo %d is done eating\n", philo->id + 1);
	philo->args->nb_meals += 1;
	philo->meal_time = get_time() - philo->init_time;
	return (NULL);
}

void	*sleeping_process(t_philo *philo)
{
	printf("philo %d is sleeping\n", philo->id + 1);
	//usleep(philo->args->time_to_sleep * 1000);
	//printf("philo %d is done sleeping\n", philo->id + 1);
	return (NULL);
}

void	*thinking_process(t_philo *philo)
{
	(void) philo;
	return (NULL);
}

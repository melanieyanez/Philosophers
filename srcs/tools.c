/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:31:08 by melanieyane       #+#    #+#             */
/*   Updated: 2023/11/17 14:41:57 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	better_sleep(int duration, t_philo *philo)
{
	long long	current_time;

	current_time = get_time();
	while (get_time() - current_time <= duration)
	{
		if (philo->args->stop)
			return ;
		if ((get_time() - current_time) >= duration)
			return ;
	}
}

void	print_actions(int time, char *action, t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->stop_mutex));
	if (!philo->args->stop)
		printf("%dms Philo %d %s\n", time, philo->id + 1, action);
	pthread_mutex_unlock(&(philo->args->stop_mutex));
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i ++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + str[i] - '0';
		else
			return (sign * result);
		i ++;
	}
	return (sign * result);
}

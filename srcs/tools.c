/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:31:08 by melanieyane       #+#    #+#             */
/*   Updated: 2023/11/13 21:00:05 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_actions(int time, char *action, t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->stop_mutex));
	if (!philo->args->stop)
		printf("%dms Philo %d %s\n", time, philo->id + 1, action);
	pthread_mutex_unlock(&(philo->args->stop_mutex));
}

int	get_time(void)
{
	struct timeval	current_time;
	static int		t = 0;

	gettimeofday(&current_time, NULL);
	if (t == 0)
		t = current_time.tv_sec;
	return (((current_time.tv_sec - t) * 1000) + (current_time.tv_usec / 1000));
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

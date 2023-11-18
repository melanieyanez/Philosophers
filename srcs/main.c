/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:46:54 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/18 18:26:23 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TO DO
//nbr de lignes du main
//custom les return avec error_message et/ou quit_program
//si on garde error_message, ajouter au header
//s'assurer qu'il y a plus de exit
//MEAL MAX à -1 ?

#include "../includes/philo.h"

void	quit_program(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		if (philo[i])
		{
			pthread_mutex_destroy(&(philo[i]->fork_mutex));
			free(philo[i]);
		}
		i ++;
	}
	if (args)
	{
		pthread_mutex_destroy(&(args->stop_mutex));
		free(args);
	}
	if (philo)
		free(philo);
}

void	parse_args(int argc, char **argv, t_args *args)
{
	args->stop = 0;
	args->nb_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_meals = ft_atoi(argv[5]);
	else
		args->nb_meals = INT_MAX;
	if (args->nb_philos < 0 || args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0 || args->nb_meals <= 0)
	{
		printf("Error: invalid arguments\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_philo	**philo;
	int		i;

	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
	if (argc == 5 || argc == 6)
		parse_args(argc, argv, args);
	else
	{
		printf("Usage: ./philo <nb_philos> <time_to_die> <time_to_eat> <time_to_sleep> <nb_meals>\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo) * args->nb_philos);
	if (!philo)
		return (1);
	i = 0;
	while (i < args->nb_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (1);
		i ++;
	}
	philo_process(philo, args);
	return (0);
}

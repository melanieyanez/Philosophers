/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:46:54 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/23 12:04:12 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*----------------------------------------------*/
/* Displays an error message and frees allocated memory. */

int	error_return(char *message, t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	if (args)
		free(args);
	if (philo)
	{
		while (philo[i])
		{
			if (philo[i])
				free(philo[i]);
			i ++;
		}
		free(philo);
	}
	return (printf("Error: %s\n", message));
}

/*----------------------------------------------*/
/* Frees allocated memory for philosophers and program parameters. */

void	quit_program(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		if (philo[i])
		{
			pthread_mutex_destroy(&(philo[i]->fork_mutex));
			pthread_mutex_destroy(&(philo[i]->status_mutex));
			free(philo[i]);
		}
		i ++;
	}
	if (args)
	{
		pthread_mutex_destroy(&(args->stop_mutex));
		pthread_mutex_destroy(&(args->write_mutex));
		free(args);
	}
	if (philo)
		free(philo);
}

/*----------------------------------------------*/
/* Parses command line arguments, initializes the parameter */
/* structure, and philosophers. */

int	parse_args(int argc, char **argv, t_philo **philo, t_args *args)
{
	if (argc != 5 && argc != 6)
	{
		return (error_return("usage: ./philo <nb_philos> <time_to_die>"
				"<time_to_eat> <time_to_sleep> [<nb_meals>]", philo, args));
	}
	args->stop = 0;
	args->nb_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_meals = ft_atoi(argv[5]);
	else
		args->nb_meals = INT_MAX;
	if (args->nb_philos <= 0 || args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0 || args->nb_meals <= 0)
	{
		return (error_return("invalid arguments", philo, args));
	}
	return (0);
}

/*----------------------------------------------*/
/* Entry point of the program. */

int	main(int argc, char **argv)
{
	t_args	*args;
	t_philo	**philo;
	int		i;

	args = malloc(sizeof(t_args));
	if (!args)
		error_return("memory allocation", NULL, NULL);
	if (parse_args(argc, argv, NULL, args) != 0)
		return (1);
	philo = malloc(sizeof(t_philo) * args->nb_philos);
	if (!philo)
		error_return("memory allocation", NULL, args);
	i = 0;
	while (i < args->nb_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			error_return("memory allocation", philo, args);
		i ++;
	}
	philo_process(philo, args);
	return (0);
}

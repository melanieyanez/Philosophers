/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:46:54 by myanez-p          #+#    #+#             */
/*   Updated: 2023/11/02 14:11:55 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	parse_args(int argc, char **argv, t_args *args)
{
	//init_args(args);
	args->nb_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_meals = ft_atoi(argv[5]);
	if (args->nb_philos < 0 || args->time_to_die < 0 || args->time_to_eat < 0 || args->time_to_sleep < 0)
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
	if (argc == 5 || argc == 6)
		parse_args(argc, argv, args);
	else
	{
		printf("Usage: ./philo <nb_philos> <time_to_die> <time_to_eat> <time_to_sleep> <nb_meals>\n");
		free(args);
		return (1);
	}
	philo = malloc(sizeof(t_philo) * args->nb_philos);
	i = 0;
	while (i < args->nb_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i;
		i ++;
	}
	philo_init(philo, args);
	return (0);
}

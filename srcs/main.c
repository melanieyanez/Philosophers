/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:46:54 by myanez-p          #+#    #+#             */
/*   Updated: 2023/10/30 17:17:54 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	parse_args(int argc, char **argv)
{
	t_args	args;

	init_args(&args);
	args.nb_philos = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.nb_meals = ft_atoi(argv[5]);
	if (args.nb_philos < 0 || args.time_to_die < 0 || args.time_to_eat < 0 || args.time_to_sleep < 0)
	{
		printf("Error: invalid arguments\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		parse_args(argc, argv);
	else
	{
		printf("Usage: ./philo <nb_philos> <time_to_die> <time_to_eat> <time_to_sleep> <nb_meals>\n");
		return (1);
	}
	return (0);
}

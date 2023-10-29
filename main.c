/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:46:54 by myanez-p          #+#    #+#             */
/*   Updated: 2023/10/29 19:11:05 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(int argc, char **argv)
{
	t_args	args;

	args.nb_philos = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.nb_meals = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		parse_args(argc, argv);
	else
	{
		printf("Usage:./philo <nb_philos> <time_to_die> <time_to_eat> \
		<time_to_sleep> <nb_meals>\n");
		return (1);
	}
	return (0);
}

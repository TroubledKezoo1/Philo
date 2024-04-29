/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:29:38 by ysarac            #+#    #+#             */
/*   Updated: 2024/04/29 16:50:12 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 2 && (ac != 5 && ac != 6))
		return (printf("Wrong Argument"), 0);
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		if (!av || !ft_check(av))
			return (printf("Split or Wrong Argument"), double_free(av), 0);
		if (!ft_initialize(&table, av) || !ft_start(&table))
			return (printf("Error"), table_free(&table), 0);
		double_free(av);
		destroyss(&table);
		table_free(&table);
		return (0);
	}
	else
		av++;
	if (!ft_check(av))
		return (printf("Wrong Argument"), 0);
	if (!ft_initialize(&table, av) || !ft_start(&table))
		return (printf("Error"), table_free(&table), 0);
	destroyss(&table);
	table_free(&table);
	return (0);
}

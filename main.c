/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:29:38 by ysarac            #+#    #+#             */
/*   Updated: 2024/03/29 02:43:37 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_table table;
	if (ac == 2)
	{
		if((av = ft_split(av[1], ' ')) == NULL)
            return (printf("Split Error"),double_free(av),0);
		if (!ft_check(av))
			return (printf("Wrong Argument"),double_free(av),0);
        if (!ft_initialize(&table, av))
			return (printf("Initialize Error"),double_free(av),0);
		if (!ft_start(&table))
			return(printf("Error"),table_free(&table),double_free(av),0);
		double_free(av);
	}
	else if (ac == 5 || ac == 6)
	{
		av++;
		if (!ft_check(av))
			return (printf("Wrong Argument"));
		if (!ft_initialize(&table, av))
			return (printf("Initialize Error"));
		if (!ft_start(&table))
			return(printf("Error"),table_free(&table),0);
	}
	else
		printf("Wrong Argument");
    return(0);
}

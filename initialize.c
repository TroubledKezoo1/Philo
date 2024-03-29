/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:31:10 by ysarac            #+#    #+#             */
/*   Updated: 2024/03/29 07:18:13 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	philo_add(t_philo **root, int id)
{
	t_philo	*newphilo;
	
	newphilo = (t_philo *)malloc(sizeof(t_philo));
	if (!newphilo)
		return (printf("Philo Error"), philo_free(root), 0);
	newphilo->id = id;
	newphilo->right_philo = newphilo;
	newphilo->left_philo = newphilo;
	if (*root == NULL)
	{
		*root = newphilo;
	}
	else
	{
		(*root)->left_philo->right_philo = newphilo;
		newphilo->left_philo = (*root)->left_philo;
		(*root)->left_philo = newphilo;
		newphilo->right_philo = *root;
	}
	return (1);
}

int	create_philo(t_table *table)
{
	int	i;

	i = 1;
	table->first_philo = NULL;
	while (i <= table->number_of_philo)
	{
		if (!philo_add(&table->first_philo, i))
			return (0);
		i++;
	}
	philo_free(&table->first_philo);
	return (1);
}

int	ft_initialize(t_table *table, char **av)
{
	table->number_of_philo = ft_atoi(av[0]);
	if (!create_philo(table))
		return (0);
	return (1);
}
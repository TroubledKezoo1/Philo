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
#include <unistd.h>


int	philo_add(t_philo **root, int id, t_table *table)
{
	t_philo	*newphilo;
	
	newphilo = (t_philo *)malloc(sizeof(t_philo));
	if (!newphilo)
		return (printf("Philo Init Error"), philo_free(root), 0);
	newphilo->id = id;
	newphilo->eat_count = 0;
	newphilo->table = table;
	newphilo->right_philo = newphilo;
	newphilo->left_philo = newphilo;
	newphilo->right_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (newphilo->right_fork == NULL)
		return (printf("Philo Right Fork Init Error"), philo_free(root), 0);
	if (*root == NULL)
		*root = newphilo;
	else
	{
		(*root)->left_fork = newphilo->right_fork;
		newphilo->left_fork = (*root)->left_philo->right_fork; 
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
		if (!philo_add(&table->first_philo, i, table))
			return (0);
		i++;
	}
	return (1);
}

int init_mutexes(t_table *table)
{
	t_philo *iter;
	int		i;

	iter = table->first_philo;
	i = 1;
	while (i <= table->number_of_philo)
	{
		if (pthread_mutex_init(iter->right_fork,NULL) != 0)
			return (0);
		iter = iter->right_philo;
		i++;
	}
	pthread_mutex_init(&table->write,NULL);
	return(1);
}

int	ft_initialize(t_table *table, char **av)
{
	table->number_of_philo = ft_atoi(av[0]);
	table->time_to_die = ft_atoi(av[1]);
	table->time_to_eat = ft_atoi(av[2]);
	table->time_to_sleap = ft_atoi(av[3]);
	table->number_of_must_eat = -1;
	if (av[4])
		table->number_of_must_eat = ft_atoi(av[4]);
	if (!create_philo(table))
		return (0);
	if (!init_mutexes(table))
		return (0);
	table->stop = 0;
	table->time = current_time();
	return (1);
}
int ft_start(t_table *table)
{
	if (table->number_of_philo == 1)
	{
		int i;
		time_usleep(table->time_to_die);
		i = time_from_start(table);
		pthread_mutex_lock(table->first_philo->right_fork);
		printf("\033[0;36m%d \033[0;32m%d %s\033[0m\n", 0, 1, TAKEN_FORK);
		printf("\033[0;36m%d \033[0;32m%d %s\033[0m\n", i, 1, DIE);
		pthread_mutex_unlock(table->first_philo->right_fork);
		pthread_mutex_destroy(table->first_philo->right_fork);
		return(1);
	}
	else if (table->number_of_philo > 1)
	{
		if(!start_thread(table))
			return(0);
	}
	return(1);	
}
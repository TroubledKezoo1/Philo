/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 07:19:21 by ysarac            #+#    #+#             */
/*   Updated: 2024/03/29 07:29:20 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	philo_free(t_philo **root)
{
	t_philo	*current;
	t_philo	*temp;

	if (*root == NULL)
		return ;
	current = *root;
	temp = NULL;
	while (current != NULL)
	{
		temp = current;
		current = current->right_philo;
		free(temp);
		if (current == *root)
			break ;
	}
	*root = NULL;
}
void	double_free(char **av)
{
	if (av != NULL)
	{
		int i;

		i = 0;
		while (av[i])
		{
			free(av[i]);
			i++;
		}
		free(av);
	}
}
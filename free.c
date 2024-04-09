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

void    table_free(t_table *table)
{
	philo_free(&table->first_philo);
}

void    philo_free(t_philo **root)
{
    if (*root == NULL)
        return;

    t_philo *current = *root;
    t_philo *next = NULL;

    while (current != NULL)
    {
        next = current->right_philo;

        // Freeing right and left forks
        free(current->right_fork);
        free(current->left_fork);

        free(current);

        current = (next == *root) ? NULL : next;
    }

    *root = NULL;
}

void    double_free(char **av)
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

int     mutex_free(pthread_mutex_t *mutex)
{
    if (mutex != NULL )
    {
        if ((pthread_mutex_unlock(mutex) != 0) && (pthread_mutex_destroy(mutex) != 0))
        {
            return(free(mutex),0);
        }
        return(1);
    }
    return(0);
}
#include "philo.h"
#include <stdio.h>
#include <pthread.h>

int	print(t_philo *philo,char* str)
{
	if (pthread_mutex_lock(&philo->table->write) != 0)
		return(mutex_free(&philo->table->write));
	printf("%llu %d.Philo ::  %s\n",time_from_start(philo->table),philo->id, str);
	if (pthread_mutex_unlock(&philo->table->write) != 0)
		return(mutex_free(&philo->table->write));
    return (1);
}

int	must_eating_check(t_table *table)
{
	t_philo *iter;
	int	i;

	if (table->number_of_must_eat < 0)
		return (0);
	i = 1;
	iter = table->first_philo;
	while (i <= table->number_of_philo)
	{
		pthread_mutex_lock(&table->count_eat);
		if (iter->eat_count < table->number_of_must_eat)
		{
			pthread_mutex_unlock(&table->count_eat);
			return (0);
		}
		else
			pthread_mutex_unlock(&table->count_eat);
		iter = iter->right_philo;
		i++;
	}
	return (1);
}


int	check_die(t_table *table)
{
	t_philo *iter;
	iter = table->first_philo;
	while (table->number_of_philo > 1)
	{
		pthread_mutex_lock(&table->eat_last);
		pthread_mutex_lock(&table->isdie);
		if((current_time() - iter->last_eat) >= table->time_to_die)
		{
			print(iter,DIE);
			pthread_mutex_lock(&table->stop_flag);
			table->stop = 1;
			pthread_mutex_unlock(&table->stop_flag);
			pthread_mutex_unlock(&table->eat_last);
			return(0);
		}
		else
			pthread_mutex_unlock(&table->eat_last);
		pthread_mutex_unlock(&table->eat_last);
		if (must_eating_check(table))
			break ;
		iter = iter->right_philo;
	}
	return (1);
}


void	die_check(t_table *table)
{
	if (table->number_of_philo == 1)
		print(table->first_philo, DIE);
	if (!(check_die(table)))
		return ;
	pthread_mutex_lock(&table->stop_flag);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_flag);
}
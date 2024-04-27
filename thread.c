#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int start_thread(t_table *table)
{
	t_philo	*iter;
	int i;

	i = 1;
	iter = table->first_philo;
	while (i <= table->number_of_philo)
	{
		if (pthread_create(&iter->thread_id,NULL,&thread_routine,iter) != 0)
			return (0);
		iter = iter->right_philo;
		i++;
	}
	i = 1;
	iter = table->first_philo;
	die_check(table);
	while (i <= table->number_of_philo)
	{
		if (pthread_join(iter->thread_id,NULL) != 0)
			return (0);
		iter = iter->right_philo;
		i++;
	}
	return (1);
}

void *thread_routine(void *arg)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		time_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->table->stop_flag);
		stop = philo->table->stop;
		pthread_mutex_unlock(&philo->table->stop_flag);
		if (stop == 1)
			break;
		if(!philo_eat(philo))
			break;
		philo_sleep(philo);
		philo_think(philo);
	}
	return(NULL);
}

int		philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_flag);
	if(philo->table->stop == 1)
	{
		pthread_mutex_unlock(&philo->table->stop_flag);
		return(0);
	}
	pthread_mutex_unlock(&philo->table->stop_flag);
	
	if (philo->eat_count == philo->table->number_of_must_eat)
		return (0);
	pthread_mutex_lock(philo->right_fork);
	print(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->left_fork);
	print(philo, TAKEN_FORK);
	print(philo, IS_EATING);
	pthread_mutex_lock(&philo->table->count_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->count_eat);
	time_usleep(philo->table->time_to_eat);

	pthread_mutex_lock(&philo->eat_check);
	philo->last_eat = current_time();
	pthread_mutex_unlock(&philo->eat_check);
	
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return(1);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_flag);
	if(philo->table->stop == 1)
	{
		pthread_mutex_unlock(&philo->table->stop_flag);
		return;
	}
	pthread_mutex_unlock(&philo->table->stop_flag);
	print(philo, IS_SLEEPING);
	time_usleep(philo->table->time_to_sleap);
}

void	philo_think(t_philo *philo)
{

	pthread_mutex_lock(&philo->table->stop_flag);
	if(philo->table->stop == 1)
	{
		pthread_mutex_unlock(&philo->table->stop_flag);
		return;
	}
	pthread_mutex_unlock(&philo->table->stop_flag);
	print(philo, IS_THINKING);
}
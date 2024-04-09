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
    t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;
    if (philo->id % 2 == 0)
		time_usleep(10);
    while (1)
    {
		philo_eat(philo);
		if (philo->eat_count == table->number_of_must_eat)
			break;
		
	}   
    return (NULL);
}

void philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	print(philo,TAKEN_FORK);
	print(philo,TAKEN_FORK);
	print(philo,IS_EATING);
	philo->eat_count++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

}
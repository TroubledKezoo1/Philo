#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int start_thread(t_table *table)
{
	t_philo	*iter;
	int i;

	i = 1;
	table->time = current_time();
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
		time_usleep(1000);
    while (1)
    {
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
		if (table->number_of_must_eat == philo->eat_count)
			break;
	}
    return (NULL);
}

void philo_eat(t_philo *philo)
{
	if (philo->eat_count == philo->table->number_of_must_eat)
			return;
	pthread_mutex_lock(philo->right_fork);
	print(philo,TAKEN_FORK);
	pthread_mutex_lock(philo->left_fork);
	print(philo,TAKEN_FORK);
	print(philo,IS_EATING);
	philo->eat_count++;
	time_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

}
void	philo_sleep(t_philo *philo)
{
	print(philo, IS_SLEEPING);
	time_usleep(philo->table->time_to_sleap);
}

void	philo_think(t_philo *philo)
{
	print(philo, IS_THINKING);
}
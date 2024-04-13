#include "philo.h"
#include <stdio.h>
int	print(t_philo *philo,char* str)
{
	if (pthread_mutex_lock(&philo->table->write) != 0)
		return(mutex_free(&philo->table->write));
	printf("%llu %d.Philo ::  %s\n",time_from_start(philo->table),philo->id, str);
	if (pthread_mutex_unlock(&philo->table->write) != 0)
		return(mutex_free(&philo->table->write));
    return (1);
}
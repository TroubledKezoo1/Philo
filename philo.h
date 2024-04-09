/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:29:24 by ysarac            #+#    #+#             */
/*   Updated: 2024/03/29 07:24:13 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

# define TAKEN_FORK "has taken a fork"
# define IS_EATING "is eating"
# define IS_SLEEPING	"is sleeping"
# define IS_THINKING "is thinking"
# define DIE "died"

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				eat_count;
	struct s_table	*table;
	struct s_philo	*right_philo;
	struct s_philo	*left_philo;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
}					t_philo;

typedef struct s_table
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleap;
	int				number_of_must_eat;
	int				stop;
	uint64_t		time;
	t_philo			*first_philo;
	pthread_mutex_t	write;
}					t_table;

int					ft_check(char **av);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				**ft_split(char const *s, char c);
int					ft_initialize(t_table *table, char **av);
void				double_free(char **av);
int					create_philo(t_table *table);
int					philo_add(t_philo **root, int id,t_table *table);
uint64_t			current_time(void);
uint64_t			time_from_start(t_table *table);
void				time_usleep(uint16_t micsec);
int 				ft_start(t_table *table);
void				philo_free(t_philo **root);
void				table_free(t_table *table);
int					start_thread(t_table *table);
int					init_mutexes(t_table *table);
void				*thread_routine(void *arg);
int					print(t_philo *philo,char *str);
int					mutex_free(pthread_mutex_t *mutex);
void				philo_eat(t_philo *philo);
#endif
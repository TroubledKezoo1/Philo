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

typedef struct s_philo
{
	int				id;
	struct s_philo	*right_philo;
	struct s_philo	*left_philo;
}					t_philo;

typedef struct s_table
{
	int				number_of_philo;
	t_philo			*first_philo;
}					t_table;

int					ft_check(char **av);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				**ft_split(char const *s, char c);
int					ft_initialize(t_table *table, char **av);
void				double_free(char **av);
int					create_philo(t_table *table);
int					philo_add(t_philo **root, int id);
void				philo_free(t_philo**root);

#endif
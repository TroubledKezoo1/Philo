#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo
{
    int id;
    struct s_philo *right_philo;
    struct s_philo *left_philo;
};

typedef struct s_table
{
    int number_of_philo;
}t_table;

int ft_check(char **av);
int ft_atoi(const char *str);
int ft_isdigit(int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);

#endif
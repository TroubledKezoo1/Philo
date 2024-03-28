int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
#include <stdio.h>
int ft_check(char **av)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (av[j])
    {
        while (av[j][i])
        {
            if (!ft_isdigit(av[j][i++]))
                return(0); 
        }
        j++;
    }
    if (j == 4 || j == 5)
    {
        while (j--)
        {
            if (ft_atoi(av[j]) <= 0 || ft_atoi(av[j]) > 2147483647)
                return(0);
        }   
    }
    else
        return (0);
    return (1);
}

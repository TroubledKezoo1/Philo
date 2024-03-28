#include <stdio.h>
#include "philo.h"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        av = ft_split(av[1],' ');
        if (!ft_check(av))
            return(printf("Wrong Argument"));
        
    }
    else if (ac == 5 || ac == 6)
    {
        av++;
        if (!ft_check(av))
            return(printf("Wrong Argument"));
    }
    else
        printf("Wrong Argument");
    
}
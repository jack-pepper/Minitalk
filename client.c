#include "../libft.h"
#include <signal.h>

int	main(int argc, char **argv)
{
	char	*msg;
	sigset_t	sigset;
	int	res;
	int	target_pid;
	int	i;

	res = 0;
	msg = NULL;
	if (argc != 3) // NB: Improve checking (types must match)
	{
		ft_putstr_fd("Error: invalid parameters\n", 2);
	}
	else
	{
		target_pid = ft_atoi(argv[1]);
		msg = argv[2];
		sigemptyset(&sigset);
		sigaddset(&sigset, SIGUSR1);
		i = 0;
		while (msg[i] != '\0')
		{
			ft_encrypt_char(target_pid, msg[i]);	
	}
	return (0);	
	}
}

// FROM LIBBIN
int     ft_is_bit_set(unsigned int num, int bit_pos)
{
        int     is_set;

        is_set = 0;
        if (bit_pos < 0 || ((unsigned int)bit_pos >= (sizeof(num) * 8)))
                return (-1);
        if(num & (1 << bit_pos))
                is_set = 1;
	return (is_set);
}

int	ft_encrypt_char(int target_pid, char *character)
{
	int	i;

	i = 0;	
	while (character != '\0')
	{
		if (is_set(character) == 0)
		{
			res = kill(target_pid, SIGUSR1);
			if (res == 0)
				ft_putstr_fd("SIGUSR1 sent\n", 1);
			else
				ft_putstr_fd("Error while sending.\n", 2);
		}
		else if (is_set(character) == 1)
		{
			res = kill(target_pid, SIGUSR2);
			if (res == 0)
				ft_putstr_fd("SIGUSR2 sent\n", 1);
			else
				ft_putstr_fd("Error while sending.\n", 2);
		}
		i++;
	}
	return (0);
}

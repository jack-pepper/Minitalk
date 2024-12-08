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
			if (msg[i])
			{
				res = kill(target_pid, SIGUSR1);
				if (res == 0)
					ft_putstr_fd("SIGUSR1 sent\n", 1);
				else
					ft_putstr_fd("Error while sending.\n", 2);
			}
			else if (msg[i])
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
}



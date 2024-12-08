#include "../libft.h"
#include <signal.h>

void	signal_handler(int signum);

int	main(void)
{
	pid_t	pid;
	struct sigaction	act;

	pid = getpid();
	ft_printf("Process ID (PID): %d\n", pid);	
	act.sa_handler = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("SIGUSR1 received\n", signum);
	else if (signum == SIGUSR2)
		ft_printf("SIGUSR2 received\n", signum);
}

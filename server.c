/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:25:28 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 21:40:28 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>
/*
 * Open two terminals. Launch ./server first in one of them.
 * Then launch ./client <SERVER_PID> <MESSAGE> in the second.
 * The message will be displayed in the first terminal.
 */
void	init_sigaction(void);
void	signal_handler(int signum, siginfo_t *info, void *ucontext);

int	main(void)
{
	pid_t					pid;

	pid = getpid();
	ft_printf("Process ID (PID): %d\n", pid);
	init_sigaction();
	while (1)
	{
		pause();
	}
	return (0);
}

void	init_sigaction(void)
{
	struct sigaction		act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	static int	i = 0;
	static char	binary[9];
	char		c;

	if (i < 8)
	{
		if (signum == SIGUSR1)
			binary[i] = '0';
		else if (signum == SIGUSR2)
			binary[i] = '1';
		i++;
	}
	if (i == 8)
	{
		binary[i] = '\0';
		c = ft_bin_to_char(binary);
		write(1, &c, 1);
		i = 0;
		ft_memset(binary, '\0', 9);
	}
	ucontext++;
	kill(info->si_pid, SIGUSR1);
}

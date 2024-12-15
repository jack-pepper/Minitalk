/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:25:28 by mmalie            #+#    #+#             */
/*   Updated: 2024/11/14 09:34:23 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO DO: create init_ functions for signal handling
 * Include ft_bin_to_char to libft
 *
 */

#include "./libft/libft.h"
#include <signal.h>

void	signal_handler(int signum, siginfo_t *info, void *ucontext);
char	ft_bin_to_char(char binary[9]);

int	main(void)
{
	struct sigaction		act;
	pid_t					pid;

	ft_memset(&act, 0, sizeof(act));
	pid = getpid();
	ft_printf("Process ID (PID): %d\n", pid);
	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
	}
	return (0);
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

// Should be in libft
char	ft_bin_to_char(char binary[9])
{
	int	ascii_val;
	int	i;

	ascii_val = 0;
	i = 0;
	while (i < 8)
	{
		if (binary[i] == '1')
			ascii_val += (1 << (7 - i));
		i++;
	}
	return ((char)ascii_val);
}

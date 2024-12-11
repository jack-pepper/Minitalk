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

#include "./libft/libft.h"
#include <signal.h>

void	signal_handler(int signum);
char	ft_bin_to_char(char binary[9]);

int	main(void)
{
	pid_t			pid;
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
}

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

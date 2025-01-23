/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:25:28 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 21:39:35 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <signal.h>
/*
 * Open two terminals. Launch ./server first in one of them.
 * Then launch ./client <SERVER_PID> <MESSAGE> in the second.
 * The message will be displayed in the first terminal.
 */
int	g_is_transmission_open = 0;

void	signal_handler(int signum);
void	init_sigaction(void);
void	init_sigset(void);
int		ft_encrypt_char(int target_pid, int character);

int	main(int argc, char **argv)
{
	char		*msg;
	int			target_pid;
	int			i;

	init_sigaction();
	i = 0;
	msg = NULL;
	if (argc != 3)
	{
		ft_putstr_fd("Error: invalid parameters\n", 2);
	}
	else
	{
		target_pid = ft_atoi(argv[1]);
		msg = argv[2];
		while ((msg[i] != '\0'))
		{
			if (ft_encrypt_char(target_pid, msg[i]) == -1)
				return (-1);
			i++;
		}
		return (0);
	}
}

void	init_sigaction(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = signal_handler;
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		g_is_transmission_open = 1;
	}
	else if (signum == SIGUSR2)
	{
		ft_printf("EOF\n");
	}
}

void	init_sigset(void)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigaddset(&sigset, SIGUSR2);
}

int	ft_encrypt_char(int target_pid, int character)
{
	int	res;
	int	i;

	i = 7;
	if (g_is_transmission_open == 0)
	{
		while (i >= 0)
		{
			if (ft_is_bit_set(character, i) == 0)
				res = kill(target_pid, SIGUSR1);
			else if (ft_is_bit_set(character, i) == 1)
				res = kill(target_pid, SIGUSR2);
			if (res != 0)
				return (-1);
			usleep(200);
			while (g_is_transmission_open == 0)
				usleep(300);
			g_is_transmission_open = 0;
			i--;
		}
	}
	return (0);
}

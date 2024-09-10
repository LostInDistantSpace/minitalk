/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:54:21 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 16:31:46 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

static int	g_receiver;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	bytes = 0;

	(void)info;
	(void)context;
	g_receiver = 1;
	if (signum == SIGUSR2)
		bytes++;
	else if (signum == SIGUSR1)
	{
		ft_printf("Bytes received : %d\n", bytes / 8);
		exit(0);
	}
}

int	send_byte(int server_pid, char byte)
{
	int		shift;

	shift = 7;
	while (shift >= 0)
	{
		if ((byte >> shift) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (!g_receiver)
			;
		g_receiver = 0;
		--shift;
	}
	return (0);
}

int	send_string(int server_pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		send_byte(server_pid, str[i++]);
	send_byte(server_pid, '\0');
	return (0);
}

void	waiter(void)
{
	int	i;

	i = 0;
	while (i < 500)
	{
		if (i == 500)
			exit (ft_printf("No server response...\n"));
		i++;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

	if (ac > 3)
		ft_printf("\nToo many arguments\n\n");
	else if (ac < 3)
		ft_printf("\nNo message to send\n\n");
	if (ac != 3)
		return (1);
	pid = ft_atoi(av[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_string(pid, av[2]);
	waiter();
	return (0);
}

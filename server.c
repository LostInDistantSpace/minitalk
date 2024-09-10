/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   server.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bmouhib <bmouhib@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/27 18:53:33 by bmouhib		   #+#	#+#			 */
/*   Updated: 2024/08/25 15:09:09 by bmouhib		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

void	ft_prompt(int serv_pid)
{
	static int	pid = 0;

	if (!pid && serv_pid)
		pid = serv_pid;
	if (!serv_pid)
		ft_printf("\n");
	ft_printf("\033[0;37m\033[1m[PID: %d ]\033[0m ", pid);
}

void	bit_handler(int signal, char *byte)
{
	if (signal == SIGUSR1)
		*byte = (*byte << 1) | 1;
	else if (signal == SIGUSR2)
		*byte <<= 1;
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	pid = 0;
	static char	c = 0;
	static int	i = 0;

	(void)context;
	if (pid == 0)
		pid = info->si_pid;
	bit_handler(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			ft_prompt(0);
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		ft_printf("%c", c);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_prompt(getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

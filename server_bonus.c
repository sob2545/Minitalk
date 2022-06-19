/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:04:25 by sesim             #+#    #+#             */
/*   Updated: 2022/06/18 10:22:11 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minitalk_bonus.h"
#include "./libft/libft.h"

void	first_hamming(unsigned int *res, unsigned char *c)
{
	(*res) = key_check(*c);
	(*res) <<= 4;
	*c = 0;
}

void	finish_transit(pid_t *client_pid, unsigned int *i)
{
	if (kill((*client_pid), SIGUSR2) == -1)
		ft_putstr_fd("Transmit Failed!\n", 2);
	(*client_pid) = 0;
	(*i) = 0;
}

void	last_hamming(unsigned int *res, unsigned char *c, \
		unsigned int *i, pid_t *client_pid)
{
	static int	flag;

	(*res) |= key_check(*c);
	hand_shaker(res, client_pid, &flag);
	if (flag != 0)
	{
		if (((*res) & 0b11111111) != 0b11111111)
			ft_putchar_fd((*res), 1);
		(*res) = 0;
		(*c) = 0;
		(*i) = 0;
		flag++;
		if (kill((*client_pid), SIGUSR1) == -1)
			ft_putstr_fd("Transmit Failed!\n", 2);
	}
}

static void	decoding(int sig, siginfo_t *info, void *context)
{
	static unsigned int		i;
	static unsigned int		res;
	static unsigned char	c ;
	static pid_t			client_pid;

	(void)context;
	client_pid = interrupt_handler(info, &i, &res, &c);
	c |= (sig == SIGUSR2);
	if (++i == 8)
		first_hamming(&res, &c);
	else if (i == 16)
	{
		if (!res)
		{
			finish_transit(&client_pid, &i);
			write(1, "\n", 1);
			return ;
		}
		last_hamming(&res, &c, &i, &client_pid);
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&s_sigaction.sa_mask);
	sigaddset(&s_sigaction.sa_mask, SIGUSR1);
	sigaddset(&s_sigaction.sa_mask, SIGUSR2);
	s_sigaction.sa_sigaction = decoding;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}

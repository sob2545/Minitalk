/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:03:49 by sesim             #+#    #+#             */
/*   Updated: 2022/06/19 20:45:58 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft/libft.h"
#include "minitalk.h"

int	g_cnt;

static void	counter(int sig)
{
	static int	received;
	static int	flag;

	if (sig == SIGUSR1)
	{
		if (flag == 0)
			ft_putstr_fd("Handshaking Success!\n", 1);
		else
			++received;
		++flag;
	}
	else
	{
		connect_checker(&flag, &received);
		ft_putstr_fd("Received Bytes: ", 1);
		ft_putnbr_fd(received, 1);
		write(1, "\n", 1);
		exit(0);
	}
}

static void	h_encoder(unsigned int *res, unsigned char *c)
{
	(*res) = key_gen((*c) >> 4);
	(*res) <<= 8;
	(*res) |= key_gen(*c);
}

static void	encoding(pid_t pid, unsigned char c)
{
	unsigned int	i;
	unsigned int	res;

	i = 16;
	h_encoder(&res, &c);
	while (i--)
	{
		if (res >> i & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_putstr_fd("Transit Failed!\n", 2);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putstr_fd("Transit Failed!\n", 2);
				exit(1);
			}
		}
		usleep(50);
	}
}

static void	send_bit(pid_t pid, char *str)
{
	unsigned int	i;

	i = 16;
	while (i--)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_putstr_fd("Invalid PID or Transit Failed!\n", 2);
			exit(1);
		}
		usleep(30);
	}
	while (*str)
		encoding(pid, (unsigned char) *str++);
	i = 16;
	while (i--)
	{
		if (kill (pid, SIGUSR1) == -1)
		{
			ft_putstr_fd("Transmit Failed!\n", 2);
			exit(1);
		}
		usleep (50);
	}
}

int	main(int argc, char **argv)
{
	pid_t	s_pid;

	s_pid = arg_checker(argc, argv[1], argv[2]);
	ft_putstr_fd("Sent Bytes    : ", 1);
	g_cnt = ft_strlen(argv[2]);
	ft_putnbr_fd(g_cnt, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, counter);
	signal(SIGUSR2, counter);
	send_bit(s_pid, argv[2]);
	while (1)
		pause();
	return (0);
}

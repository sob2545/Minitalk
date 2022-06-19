/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 07:56:44 by sesim             #+#    #+#             */
/*   Updated: 2022/06/18 08:59:36 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"
#include <unistd.h>

void	hand_shaker(unsigned int *res, pid_t *client_pid, int *flag)
{
	if ((((*res) & 0b11111111) == 0b11111111) && (*flag >= 0))
	{
		if (*flag > 1)
			write(1, "\n", 1);
		ft_putstr_fd("Handshaking Success!\n", 1);
		if (kill((*client_pid), SIGUSR1) == -1)
			ft_putstr_fd("Transmit Failed\n", 2);
		(*flag)++;
	}
	else if ((((*res) & 0b11111111) != 0b11111111) && (*flag == 0))
		ft_putstr_fd("Handshaking Failed\n", 2);
}

int	interrupt_handler(siginfo_t *info, unsigned int *i, \
		unsigned int *res, unsigned char *c)
{
	static pid_t	client_pid;

	client_pid = 0;
	if (!client_pid)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)
	{
		if (kill(client_pid, SIGUSR2) == -1)
			ft_putstr_fd("Transmit Failed!\n", 2);
		if (kill(info->si_pid, SIGUSR2) == -1)
			ft_putstr_fd("Transmit Failed!\n", 2);
		*i = 0;
		*res = 0;
		*c = 0;
	}
	return (client_pid);
}

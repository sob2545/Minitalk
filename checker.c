/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:13:21 by sesim             #+#    #+#             */
/*   Updated: 2022/06/19 20:51:04 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"

extern int	g_cnt;

void	connect_checker(int *flag, int *received)
{
	if ((*flag) == 0)
	{
		ft_putstr_fd("Handshaking Failed!\n", 2);
		exit(1);
	}
	if ((*received) != g_cnt)
	{
		ft_putstr_fd("Transmit Failed or Signal Interrupted!\n", 2);
		exit(1);
	}
}

pid_t	arg_checker(int argc, char *pid, char *argv)
{
	pid_t	s_pid;

	if (argc != 3 || !ft_strlen(argv))
	{
		ft_putstr_fd("Invalid Arguments!\n", 2);
		exit(1);
	}
	s_pid = ft_adtoi(pid);
	if ((s_pid < 100) || (s_pid > 99998) || !s_pid)
	{
		ft_putstr_fd("Invalid Server PID!\n", 2);
		exit(1);
	}
	return (s_pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:50:15 by sesim             #+#    #+#             */
/*   Updated: 2022/06/19 20:46:34 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H

# include <signal.h>

void			connect_checker(int *flag, int *received);
void			hand_shaker(unsigned int *res, pid_t *client_pid, int *flag);
int				interrupt_handler(siginfo_t *info, unsigned int *i, \
		unsigned int *res, unsigned char *c);
pid_t			arg_checker(int argc, char *pid, char *argv);
unsigned char	key_check(int bit_8);
unsigned char	key_gen(int bit_4);

#endif

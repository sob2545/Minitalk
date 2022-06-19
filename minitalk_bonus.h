/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:50:15 by sesim             #+#    #+#             */
/*   Updated: 2022/06/18 09:25:09 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H

# define MINITALK_BONUS_H

# include <signal.h>

void			connect_checker(int *flag, int *received);
void			hand_shaker(unsigned int *res, pid_t *client_pid, int *flag);
int				interrupt_handler(siginfo_t *info, unsigned int *i, \
		unsigned int *res, unsigned char *c);
unsigned char	key_check(int bit_8);
unsigned char	key_gen(int bit_4);

#endif

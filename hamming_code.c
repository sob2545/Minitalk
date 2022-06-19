/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hamming_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:35:21 by sesim             #+#    #+#             */
/*   Updated: 2022/06/15 11:04:30 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

static int	*arr_gen(unsigned char bit_8)
{
	int	*bit;
	int	i;
	int	s;

	bit = ft_calloc(8, sizeof(int));
	if (bit == 0)
		return (0);
	i = 8;
	s = 0;
	while (i-- && (s < 8))
	{
		if (((bit_8 >> (s++)) & 0b0001) == 0b0001)
			bit[i] = 1;
		else
			bit[i] = 0;
	}
	return (bit);
}

static unsigned char	bit_gen(int *bit, int i)
{
	int	res;
	int	flag;

	res = 0;
	flag = i;
	while (i < 8)
	{
		res |= bit[i];
		if (i != 7)
			res <<= 1;
		if ((flag != 0) && i == 7)
		{
			res <<= 1;
			res |= bit[3];
		}
		i++;
	}
	return (res);
}

unsigned char	key_check(int bit_8)
{
	int	*bit;
	int	i;
	int	p;

	bit = arr_gen(bit_8);
	if (bit == 0)
		return (0);
	i = 0;
	p = 0;
	while (i++ < 8)
	{
		if (bit[i] == 1)
			p ^= i;
	}
	if (p != 0)
	{
		if (bit[p] == 1)
			bit[p] = 0;
		else
			bit[p] = 1;
	}
	p = bit_gen(bit, 5);
	free (bit);
	bit = 0;
	return ((unsigned char)p);
}

unsigned char	key_gen(int bit_4)
{
	int	bit[8];
	int	i;

	ft_bzero(bit, sizeof(bit));
	if ((bit_4 & 8) == 0b1000)
		bit[5] = 1;
	if ((bit_4 & 4) == 0b0100)
		bit[6] = 1;
	if ((bit_4 & 2) == 0b0010)
		bit[7] = 1;
	if ((bit_4 & 1) == 0b0001)
		bit[3] = 1;
	bit[1] = (bit[3] ^ bit[5] ^ bit[7]);
	bit[2] = (bit[3] ^ bit[6] ^ bit[7]);
	bit[4] = (bit[5] ^ bit[6] ^ bit[7]);
	i = 0;
	while (i < 8)
		bit[0] ^= bit[i++];
	return ((unsigned char)bit_gen(bit, 0));
}

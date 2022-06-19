# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 11:16:18 by sesim             #+#    #+#              #
#    Updated: 2022/06/18 09:20:17 by sesim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

OBJS_S = server.o \
		 handler.o \
		 hamming_code.o

OBJS_C = client.o \
		 checker.o \
		 hamming_code.o

OBJS_S_BONUS = server_bonus.o \
			   handler.o \
			   hamming_code.o

OBJS_C_BONUS = client_bonus.o \
			   checker.o \
			   hamming_code.o

ifdef WITH_BONUS
	S_OB = $(OBJS_S_BONUS)
	C_OB = $(OBJS_C_BONUS)
else
	S_OB = $(OBJS_S)
	C_OB = $(OBJS_C)
endif

NAME = server client

all : $(NAME)

bonus :
	make WITH_BONUS=1 all

server : $(S_OB)
	make -C libft
	$(CC) $(CFLAGS) -o $@ $^ -L libft -l ft

client : $(C_OB)
	$(CC) $(CFLAGS) -o $@ $^ -L libft -l ft

server.o : server.c
	$(CC) $(CFLAGS) -c $^

server_bonus.o : server_bonus.c
	$(CC) $(CFLAGS) -c $^

client.o : client.c
	$(CC) $(CFLAGS) -c $^

client_bonus.o : client_bonus.c
	$(CC) $(CFLAGS) -c $^

hamming_code.o : hamming_code.c
	$(CC) $(CFLAGS) -c $^

handler.o : handler.c
	$(CC) $(CFLAGS) -c $^

checker.o : checker.c
	$(CC) $(CFLAGS) -c $^

clean :
	make -C libft clean
	$(RM) $(OBJS_C) $(OBJS_S) $(OBJS_C_BONUS) $(OBJS_S_BONUS)

fclean : clean
	make -C libft fclean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHNOY : libft all clean fclean re bonus

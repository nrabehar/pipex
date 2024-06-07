NAME= libftprintf.a

TEST_PATH = $(shell pwd)/main.c

SRCDIR= srcs
SRCFILES = ft_pf_core.c \
		ft_pf_flags.c \
		ft_pf_flags_utils.c \
		ft_pf_hex_helper.c \
		ft_pf_nbr_utils.c \
		ft_printf.c \
		ft_pf_putc.c \
		ft_pf_puthex.c \
		ft_pf_putn.c \
		ft_pf_putu.c \
		ft_pf_putp.c \
		ft_pf_puts.c \
		ft_pf_putzu.c \
		ft_pf_utils.c

OBJS_DIR = objs
OBJS = ${addprefix ${OBJS_DIR}/, ${SRCFILES:.c=.o}}

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./

${OBJS_DIR}/%.o: ${SRCDIR}/%.c
	@if [ -e $(OBJS_DIR) ]; then \
		printf ""; \
	else \
		mkdir $(OBJS_DIR); \
	fi
	@${CC} ${CFLAGS} -g -c $< -o $@

${NAME}: ${OBJS}
	@ar rsc ${NAME} ${OBJS}
	@ranlib ${NAME};

all: ${NAME}

clean:
	@rm -rf ${OBJS_DIR}

fclean: clean
	@rm -f ${NAME}

re:	fclean all

.PHONY: clean fclean all re

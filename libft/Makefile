NAME = libft.a
PF_DIR = ft_printf
PF_LIB = ${PF_DIR}/libftprintf.a

CTYPE_DIR = ctype
CTYPE_SRCS = ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_isupper.c \
	ft_islower.c \
	ft_isblank.c \
	ft_iscloser.c \
	ft_isopener.c

LIST_DIR = list
LIST_SRCS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_llst.c \
	ft_llst_utils.c

STDLIB_DIR = stdlib
STDLIB_SRCS = ft_atoi.c \
	ft_atol.c \
	ft_atoi_base.c \
	ft_calloc.c

STDIO_DIR = stdio
STDIO_SRCS = ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c

STR_DIR = strings
STR_SRCS = ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_bct_split.c \
	ft_itoa.c \
	ft_ltoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strnrcmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_strdup.c

UTL_DIR = utils
UTL_SRCS = ft_free_tab.c

GNL_DIR = get_next_line
GNL_SRCS = ft_gnl.c

SRCS = ${CTYPE_SRCS} ${STDLIB_SRCS} ${STR_SRCS} ${STDIO_SRCS}


OBJS_DIR = objs
CTYPE_OBJS = ${addprefix ${OBJS_DIR}/, ${CTYPE_SRCS:.c=.o}}
LIST_OBJS = ${addprefix ${OBJS_DIR}/, ${LIST_SRCS:.c=.o}}
STDLIB_OBJS = ${addprefix ${OBJS_DIR}/, ${STDLIB_SRCS:.c=.o}}
STDIO_OBJS = ${addprefix ${OBJS_DIR}/, ${STDIO_SRCS:.c=.o}}
STR_OBJS = ${addprefix ${OBJS_DIR}/, ${STR_SRCS:.c=.o}}
UTL_OBJS = ${addprefix ${OBJS_DIR}/, ${UTL_SRCS:.c=.o}}
GNL_OBJS = ${addprefix ${OBJS_DIR}/, ${GNL_SRCS:.c=.o}}
OBJS = ${CTYPE_OBJS} ${LIST_OBJS} ${STDLIB_OBJS} ${STDIO_OBJS} ${STR_OBJS} ${UTL_OBJS} ${GNL_OBJS}

CC = gcc

CFLAGS = -Wall -Wextra -Werror


${OBJS_DIR}/%.o : ${CTYPE_DIR}/%.c
	@if [ -e $(OBJS_DIR) ]; then \
		printf ""; \
	else \
		mkdir $(OBJS_DIR); \
	fi
	@printf "\b\e[1;32m/\e[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\b\e[1;32m-\e[0m"

${OBJS_DIR}/%.o : ${LIST_DIR}/%.c
	@if [ -e $(OBJS_DIR) ]; then \
		printf ""; \
	else \
		mkdir $(OBJS_DIR); \
	fi
	@printf "\b\e[1;32m/\e[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\b\e[1;32m-\e[0m"

${OBJS_DIR}/%.o : ${STDLIB_DIR}/%.c
	@if [ -e $(OBJS_DIR) ]; then \
		printf ""; \
	else \
		mkdir $(OBJS_DIR); \
	fi
	@printf "\b\e[1;32m/\e[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\b\e[1;32m-\e[0m"

${OBJS_DIR}/%.o : ${STDIO_DIR}/%.c
	@if [ -e $(OBJS_DIR) ]; then \
		printf ""; \
	else \
		mkdir $(OBJS_DIR); \
	fi
	@printf "\b\e[1;32m/\e[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\b\e[1;32m-\e[0m"

${OBJS_DIR}/%.o : ${STR_DIR}/%.c
	@if [ -e $(OBJS_DIR) ]; then \
		printf ""; \
	else \
		mkdir $(OBJS_DIR); \
	fi
	@printf "\b\e[1;32m/\e[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\b\e[1;32m-\e[0m"

${OBJS_DIR}/%.o : ${UTL_DIR}/%.c
	@if [ -e $(OBJS_DIR) ]; then \
		printf ""; \
	else \
		mkdir $(OBJS_DIR); \
	fi
	@printf "\b\e[1;32m/\e[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\b\e[1;32m-\e[0m"

${OBJS_DIR}/%.o : ${GNL_DIR}/%.c
	@if [ -e $(OBJS_DIR) ]; then \
		printf ""; \
	else \
		mkdir $(OBJS_DIR); \
	fi
	@printf "\b\e[1;32m/\e[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\b\e[1;32m-\e[0m"

${NAME} : ${PF_LIB} ${OBJS}
	@cp ${PF_LIB} ${NAME}
	@ar -rsc $(NAME) $(OBJS)
	@printf "\b\e[1;32m🗸 $(NAME) compiled\e[0m\n"

${PF_LIB} :
	@${MAKE} -C ${PF_DIR} --no-print-directory

all : ${NAME}

bonus : all

clean :
	@printf "\e[31m🗑 libft objects "
	@${MAKE} -C ${PF_DIR} clean --no-print-directory
	@rm -rf ${OBJS_DIR}
	@printf "\e[1;32m🗸\e[0m\n"

fclean : clean
	@printf "\e[1;31m✖️ $(NAME) "
	@rm -f $(NAME) ${PF_LIB}
	@printf "\e[1;32m🗸\e[0m\n"

re : fclean all

.PHONY : clean fclean all re bonus
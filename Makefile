# directories
LIBFT_DIR = libft
OBJS_DIR  = obj
SRCS_DIR  = src
INCS_DIR  = inc

# build
NAME = pipex
LIBPIPEX = libpipex.a
LIBFT = $(LIBFT_DIR)/libft.a

# vars
INFILE :=
CMD1 :=
CMD2 :=
OUTFILE :=

# files
SRCS_FILES = ft_utils.c \
					ft_process.c

# objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))
PM_OBJ = $(addprefix $(OBJS_DIR)/, pipex.o)
PB_OBJ = $(addprefix $(OBJS_DIR)/, pipex_bonus.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLINKS = -L./$(LIBFT_DIR) -lft -I $(INCS_DIR)
VG_FLAGS =  -s --leak-check=full --show-leak-kinds=all --track-origins=yes

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@if [ ! -e $(OBJS_DIR) ]; then \
		mkdir $(OBJS_DIR); \
	fi
	$(CC) $(CFLAGS) -c $< -o $@ $(CLINKS)

$(NAME) : $(PM_OBJ) $(LIBPIPEX)
	rm -f $(PB_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(PM_OBJ) -o $(NAME) -L. -lpipex $(CLINKS)

$(LIBPIPEX) : $(LIBFT) $(OBJS)
	@ar -rcs $(LIBPIPEX) $(OBJS)

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

test : $(NAME)
	@date
	@./$(NAME) $(INFILE) $(CMD1) $(CMD2) $(OUTFILE)
	@date


leak : $(NAME)
	@date
	@valgrind $(VG_FLAGS) ./$(NAME) $(INFILE) $(CMD1) $(CMD2) $(OUTFILE)
	@date

all : $(NAME)

bonus : $(PB_OBJ) $(LIBPIPEX)
	rm -f $(PM_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(PB_OBJ) -o $(NAME) -L. -lpipex $(CLINKS)

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	rm -f $(LIBPIPEX) $(NAME)

re : fclean all

.PHONY : re fclean clean all leak test bonus
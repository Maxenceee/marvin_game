MANDATORY_DIR	=	sources
EXECS_DIR		=	tools
OBJ_DIR			=	.objs

SRCS			=	$(shell find $(MANDATORY_DIR) -name "*.c")
OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# EXECS_SRCS		=	$(shell find $(EXECS_DIR) -name "*.c")
# EXECS_OBJS		=	$(patsubst $(EXECS_DIR)%.c, $(OBJ_DIR)%.o, $(EXECS_SRCS))

HEADER_SRCS		=	marvin_game.h
HEADERS_DIR		=	includes/
HEADERS			=	$(addprefix $(HEADERS_DIR), $(HEADER_SRCS))
CC				=	cc
RM				=	rm -f
CFLAGS			=	-g3#-Wall -Wextra -Werror
LIBS			=	-lpthread 
NAME			=	marvin_game

GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
RED				=	\033[1;31m
YELLOW      	=	\033[1;33m
DEFAULT			=	\033[0m
UP				=	"\033[A"
CUT				=	"\033[K"

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf ${UP}${CUT}

# $(OBJ_DIR)/%.o: $(EXECS_DIR)/%.c $(HEADERS) Makefile
# 	@mkdir -p $(OBJ_DIR)
# 	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
# 	@$(CC) $(CFLAGS) -c $< -o $@
# 	@printf ${UP}${CUT}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

execs: $(EXECS_OBJS)
	$(CC) $(EXECS_DIR)/poison.c -o poison
	$(CC) $(EXECS_DIR)/healer.c -o healer
	@echo "$(GREEN)poison compiled!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus
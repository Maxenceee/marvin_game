MANDATORY_DIR	=	sources
EXECS_DIR		=	tools
UTILS_DIR		=	utils
EXECS_DIR		=	tools
OBJ_DIR			=	.objs

SRCS			=	$(shell find $(MANDATORY_DIR) -name "*.c")
SRCS_UTILS		=	$(shell find $(UTILS_DIR) -name "*.c")

OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
OBJS_UTILS		=	$(patsubst $(UTILS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS_UTILS))

HEADER_SRCS		=	marvin_game.h
HEADERS_DIR		=	includes/
HEADERS			=	$(addprefix $(HEADERS_DIR), $(HEADER_SRCS))

# U_HEADER_SRCS	=	tools.h process.h
# U_HEADERS_DIR	=	$(UTILS_DIR)
# U_HEADERS		=	$(addprefix $(U_HEADERS_DIR), $(U_HEADER_SRCS))
CC				=	cc
RM				=	rm -f
CFLAGS			=	-g3 # -Wall -Wextra -Werror
LIBS			=	-lpthread 
NAME			=	marvin_game
POISON_NAME		=	poison
HEALER_NAME		=	healer

# ifeq ($(shell uname), Darwin)
#     CFLAGS += -framework CoreFoundation -framework CoreGraphics
# endif

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

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c Makefile
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf ${UP}${CUT}

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_UTILS)
	@$(CC) $(OBJS) $(OBJS_UTILS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

execs: $(OBJS_UTILS) $(EXECS_DIR)/poison.c $(EXECS_DIR)/healer.c
	@$(CC) $(OBJS_UTILS) $(EXECS_DIR)/poison.c -o $(POISON_NAME)
	@echo "$(GREEN)$(POISON_NAME) compiled!$(DEFAULT)"
	@$(CC) $(OBJS_UTILS) $(EXECS_DIR)/healer.c -o $(HEALER_NAME)
	@echo "$(GREEN)$(HEALER_NAME) compiled!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@$(RM) $(NAME)
	@echo "$(RED)Cleaning $(POISON_NAME)$(DEFAULT)"
	@$(RM) $(POISON_NAME)
	@echo "$(RED)Cleaning $(HEALER_NAME)$(DEFAULT)"
	@$(RM) $(HEALER_NAME)

re:				fclean all execs

gen:			all execs 
				./marvin_game $(GVAR)

.PHONY:			all clean fclean re execs gen
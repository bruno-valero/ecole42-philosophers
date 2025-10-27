# ============== CUSTOM TEXT =================
BOLD=\033[1m
RESET=\033[0m
LIGHT_RED=\033[91m
LIGHT_GREEN=\033[92m
LIGHT_CYAN=\033[96m

# ============== MAIN INFO =================
NAME = philo

# ============== COMPILATION COMMANDS =================
INCLUDES = -I includes
CC = cc
# CFLAGS = -Wall -Werror -Wextra -g3 -Ofast -march=native -flto -funroll-loops $(INCLUDES)
CFLAGS = -Wall -Werror -Wextra -g3 -pthread $(INCLUDES)

# ============== SRC FILES =================

SRC_FILES = src/validate_input.c src/state.c src/state_utils.c src/philo.c src/actions_utils.c src/actions.c src/millis.c src/utils.c src/philo_utils.c src/monitor.c

# ============== PROGRAM FILES =================
MAIN_PROGRAM=src/main.c

# ============== CUSOM SLEEP =================
SLEEP = 0.07

# ============== COMPILATION =================
OBJS = $(SRC_FILES:%.c=%.o)
OBJ_MAIN_PROGRAM = $(MAIN_PROGRAM:%.c=%.o)
COMPILATION_DEPENDENCIES = $(OBJS) $(OBJ_MAIN_PROGRAM)


# ***************************************************************************************************
# ********************************************           ********************************************
# ********************************************  TARGETS  ********************************************
# ********************************************           ********************************************
# ***************************************************************************************************

all: $(NAME)

$(NAME): $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$<$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(MLX_DIR) SLEEP="$(SLEEP)"

minilibx:
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(MLX_DIR) SLEEP="$(SLEEP)"


clean:
	@echo "$(LIGHT_RED)>> $(BOLD)cleanning$(RESET) $(LIGHT_CYAN)./src$(RESET)..." && sleep $(SLEEP)
	@rm -rf $(COMPILATION_DEPENDENCIES)

fclean: clean
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) $(LIGHT_CYAN)./$(NAME)$(RESET)..." && sleep $(SLEEP)
	@rm -rf $(NAME)
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) $(LIGHT_CYAN)./$(BONUS)$(RESET)..." && sleep $(SLEEP)
	@rm -rf $(BONUS)

re: fclean all

.PHONY: all clean fclean re minilibx

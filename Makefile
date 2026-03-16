# =======================
#         VARIABLES
# =======================
NAME        := philo
CC          := gcc
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := include
CFLAGS      := -Wall -Wextra -Werror -g -O3 -I$(INC_DIR)
LDFLAGS     := -lpthread

# CAMBIO AQUÍ: La lista debe coincidir exactamente con tus archivos en src/
SRC_FILES   := main.c init.c monitor.c routine.c utils.c

SRC         := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# =======================
#         COLORES
# =======================
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
RED     := \033[0;31m
RESET   := \033[0m

# =======================
#         REGLAS
# =======================
all: $(NAME)

# Eliminamos la dependencia directa de $(INC_DIR)/*.h para evitar errores si no hay varios .h
$(NAME): $(OBJ)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)✔ Build completed: $(NAME)$(RESET)"

# Esta regla ahora busca correctamente en src/ y guarda en obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Removing object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

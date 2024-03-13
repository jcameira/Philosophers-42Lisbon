NAME				=	philo

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I $(INCLUDES)
SANITIZE			=	-g -fsanitize=thread -pthread
RANDOM_MALLOC		=	-Xlinker --wrap=malloc
AR					=	ar rcs
RM					=	rm -rf

INCLUDES			=	includes/
DEFAULT_INCLUDES	=	-I /usr/local/includes

SRCS				=	error_handling.c inits.c main.c memory_handle.c philo_utils.c philo.c sim_end_check.c #malloc.c
SRCS_PATH			=	srcs/

BONUS_SRCS			=	error_handling.c main.c philo_utils.c #malloc.c
BONUS_SRCS_PATH		=	srcs_bonus/

OBJ_DIR				=	objects/
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)%.o)
BONUS_OBJS			=	$(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)
ALL_OBJECTS			=	$(OBJ_DIR)*.o

TOTAL_SRCS			=	$(words $(SRCS))
TOTAL_BONUS_SRCS	=	$(words $(BONUS_SRCS))
TOTAL_OBJS			=	$(words $(wildcard $(OBJ_DIR)*))
FILES				=	0

$(OBJ_DIR)%.o:		$(SRCS_PATH)%.c
					@$(CC) $(CFLAGS) $(DEFAULT_INCLUDES) -c $< -o $@ && \
					$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@)

$(OBJ_DIR)%.o:		$(BONUS_SRCS_PATH)%.c
					@$(CC) $(CFLAGS) $(DEFAULT_INCLUDES) -c $< -o $@ && \
					$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_BONUS_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@)

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"
					@if norminette | grep -q -v "OK!"; then \
						norminette | grep -v OK!; echo "Norminette has$(RED) errors!$(DEFAULT)"; \
					else \
						echo "Norminette$(GRN) OK!!$(DEFAULT)"; \
					fi

sanitize:			$(OBJ_DIR) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

random_m:			$(OBJ_DIR) $(OBJS)
					@$(CC) $(CFLAGS) $(SANITIZE) $(RANDOM_MALLOC) $(OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

bonus:				$(OBJ_DIR) $(BONUS_OBJS)
					@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"
					@if norminette | grep -q -v "OK!"; then \
						norminette | grep -v OK!; echo "Norminette has$(RED) errors!$(DEFAULT)"; \
					else \
						echo "Norminette$(GRN) OK!!$(DEFAULT)"; \
					fi

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

clean:				
					@$(foreach file,$(wildcard $(OBJ_DIR)*), \
						$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
						$(call PRINT_PROGRESS,$(TOTAL_OBJS),$(RED),$(YELLOW)Deleting$(DEFAULT) $(file)); \
						$(RM) $(file); \
					)
					@$(RM) $(OBJ_DIR)
					@echo "\033[2F\033[0K$(PURPLE)$(OBJ_DIR)$(DEFAULT) deleted\033[E"
					$(eval FILES=0)

fclean:				clean
					@$(RM) $(NAME)
					@echo "$(PURPLE)$(NAME)$(DEFAULT) deleted"

re:					fclean all

.PHONY:				all sanitize random_m clean fclean re

define PRINT_PROGRESS
    if [ "$(FILES)" -eq "1" ]; then \
        printf "\033[0K$(3)\n["; \
    else \
        printf "\033[0K\033[1F\033[0K$(3)\n["; \
    fi
    @for i in `seq 1 $(shell expr $(FILES) \* 70 / $(1))`; do \
        printf "$(2)=\033[0m"; \
    done
    @for i in `seq 1 $(shell expr 70 - $(FILES) \* 70 / $(1))`; do \
        printf " "; \
    done
    @printf "] $(shell echo $$(($(FILES) * 100 / $(1))))%%"
	if [ "$(FILES)" -eq "$(1)" ]; then \
        printf "\n"; \
	fi
endef

CYAN				=	\033[36m
PURPLE				=	\033[35m
YELLOW				=	\033[33m
GRN					=	\033[32m
RED					=	\033[31m
DEFAULT				=	\033[0m
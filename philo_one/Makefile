# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: larosale <larosale@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 04:34:46 by larosale          #+#    #+#              #
#    Updated: 2020/12/09 14:33:52 by larosale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo_one
CFLAGS			= -Wall -Werror -Wextra
NODEPS			= clean fclean re
SRCS			= philo_one.c philo_actions.c philo_init.c philo_utils.c \
				philo_monitor.c philo_destroy.c \
				utils_print.c utils_atoi.c utils_calloc.c errman.c
HDRS			= philo.h
OBJS			= $(SRCS:.c=.o)
DEPS			= $(SRCS:.c=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully \
	compiled $(NAME)\033[0m"

# Include all .d dependency files to the Makefile.
# Including dependencies is conditional - it shall not work when cleaning.

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif

# Generate a dependency file for each source file

%.d: %.c $(HDRS)
	@$(CC) $(CFLAGS) $< -MM -MF $@

# Dependencies for .o files are automatically merged with the dependencies from
# .d file for each object

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[90m[\033[32mOK\033[90m]\033[34m Compiling $<\033[0m"

.PHONY: bonus
bonus: all

.PHONY: clean
clean:
	@rm -f $(OBJS) $(DEPS)
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object and temp files \
	for $(NAME) were deleted\033[0m"

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Executable $(NAME) \
	was deleted\033[0m"

.PHONY: re
re: fclean all

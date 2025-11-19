# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2024/01/01 10:00:00 by marvin            #+#    #+#             #
#    Updated: 2024/01/01 10:00:00 by marvin           ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = mutantstack

# Compiler and flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Source files
SRCDIR = .
SOURCES = main.cpp

# Object files
OBJDIR = obj
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Include directories
INCLUDES = -I.

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)✓ Executable cleaned!$(RESET)"

re: fclean all

# Test rules
test: $(NAME)
	@echo "$(CYAN)Running MutantStack tests...$(RESET)"
	@./$(NAME)

# Valgrind test (if available)
valgrind: $(NAME)
	@echo "$(MAGENTA)Running valgrind memory check...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# Display help
help:
	@echo "$(WHITE)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)      - Build the program"
	@echo "  $(BLUE)clean$(RESET)    - Remove object files"
	@echo "  $(RED)fclean$(RESET)   - Remove object files and executable"
	@echo "  $(YELLOW)re$(RESET)       - Rebuild everything"
	@echo "  $(CYAN)test$(RESET)     - Build and run tests"
	@echo "  $(MAGENTA)valgrind$(RESET) - Run with valgrind (memory check)"
	@echo "  $(WHITE)help$(RESET)     - Show this help message"

# Phony targets
.PHONY: all clean fclean re test valgrind help

# Prevent make from considering files with these names
.SILENT:

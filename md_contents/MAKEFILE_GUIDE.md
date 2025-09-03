# Makefile Guide - Complete Reference

## 📚 What is a Makefile?

A **Makefile** is a build automation tool that defines how to compile and link programs. It tracks dependencies between files and only rebuilds what's necessary when source files change.

---

## 🎯 Basic Syntax

### Target-Dependency-Command Structure:
```makefile
target: dependencies
	command
	command
```

**Important**: Commands must be indented with a **TAB**, not spaces!

---

## 🔧 Basic Example (C Program)

```makefile
# Simple C program compilation
program: main.c utils.c
	gcc -o program main.c utils.c

clean:
	rm -f program
```

---

## 📋 Variables

### Variable Definition:
```makefile
# Define variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = my_program
SOURCES = main.c utils.c helper.c

# Use variables with $(VAR) or ${VAR}
$(NAME): $(SOURCES)
	$(CC) $(CFLAGS) -o $(NAME) $(SOURCES)
```

### Common Variables:
```makefile
CC = gcc                    # Compiler
CFLAGS = -Wall -Wextra     # Compiler flags
LDFLAGS = -lm              # Linker flags
NAME = program             # Executable name
SRCDIR = src               # Source directory
OBJDIR = obj               # Object directory
```

---

## 🌟 Wildcards and Pattern Rules

### Wildcards:
```makefile
# * matches any string
SOURCES = *.c              # All .c files in current directory
SOURCES = src/*.c          # All .c files in src/

# Get all .c files recursively
SOURCES = $(wildcard *.c src/*.c)
```

### Pattern Rules:
```makefile
# Convert .c files to .o files
SOURCES = main.c utils.c helper.c
OBJECTS = $(SOURCES:.c=.o)  # main.o utils.o helper.o

# Pattern rule: how to make .o from .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

### Automatic Variables:
```makefile
# $@ = target name
# $< = first dependency
# $^ = all dependencies
# $? = dependencies newer than target

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
#                     ^     ^
#                  first   target
#                   dep
```

---

## 🏗️ Advanced Makefile Structure

### Complete C Project Makefile:
```makefile
# **************************************************************************** #
#                                PROJECT SETUP                                 #
# **************************************************************************** #

NAME        = my_program
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -std=c99
RM          = rm -f

# **************************************************************************** #
#                               DIRECTORIES                                    #
# **************************************************************************** #

SRCDIR      = src
OBJDIR      = obj
INCDIR      = include

# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

SOURCES     = main.c utils.c parser.c
# Alternative: auto-find all .c files
# SOURCES   = $(wildcard $(SRCDIR)/*.c)

OBJECTS     = $(SOURCES:%.c=$(OBJDIR)/%.o)

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(NAME) created successfully!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(RM) -r $(OBJDIR)

fclean: clean
	@echo "Removing $(NAME)..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

## 📁 Directory Structure Example

```
project/
├── Makefile
├── include/
│   └── project.h
├── src/
│   ├── main.c
│   ├── utils.c
│   └── parser.c
└── obj/           # Created automatically
    ├── main.o
    ├── utils.o
    └── parser.o
```

---

## 🎮 Advanced Features

### 1. **Conditional Compilation**:
```makefile
# Debug vs Release build
DEBUG ?= 0

ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -O2 -DRELEASE
endif
```

### 2. **Multiple Source Directories**:
```makefile
SRCDIR      = src
SUBDIRS     = $(SRCDIR)/parser $(SRCDIR)/utils $(SRCDIR)/network

SOURCES     = $(wildcard $(SRCDIR)/*.c)
SOURCES     += $(wildcard $(SRCDIR)/parser/*.c)
SOURCES     += $(wildcard $(SRCDIR)/utils/*.c)

# Generate object paths
OBJECTS     = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
```

### 3. **Header Dependencies**:
```makefile
# Include header dependencies
HEADERS     = $(wildcard $(INCDIR)/*.h)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@
```

### 4. **Library Linking**:
```makefile
# External libraries
LDFLAGS     = -lm -lpthread -lcurl

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)
```

---

## 🔄 Common Patterns

### 1. **École 42 Style Makefile**:
```makefile
NAME        = program
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

SRCDIR      = .
OBJDIR      = obj

SOURCES     = main.c file1.c file2.c
OBJECTS     = $(SOURCES:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

### 2. **Multi-File Project**:
```makefile
NAME        = calculator

SOURCES     = main.c \
              operations/add.c \
              operations/subtract.c \
              utils/parser.c \
              utils/validator.c

OBJECTS     = $(SOURCES:%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	gcc -o $(NAME) $(OBJECTS)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

## 🛠️ Useful Functions

### String Manipulation:
```makefile
# Substitution
SOURCES = main.c utils.c
OBJECTS = $(SOURCES:.c=.o)                    # main.o utils.o
OBJECTS = $(SOURCES:%.c=obj/%.o)              # obj/main.o obj/utils.o

# Directory functions
DIRS = $(dir src/main.c src/utils.c)          # src/ src/
FILES = $(notdir src/main.c src/utils.c)      # main.c utils.c

# Filtering
C_FILES = $(filter %.c, main.c readme.txt)   # main.c
NO_MAIN = $(filter-out main.c, $(SOURCES))   # All except main.c
```

### File Operations:
```makefile
# Check if file exists
ifeq ($(wildcard config.h),)
    $(error config.h not found!)
endif

# Create directories
$(OBJDIR):
	mkdir -p $(OBJDIR)
```

---

## 🎯 Best Practices

### 1. **Use Variables**:
```makefile
# GOOD
CC = gcc
$(CC) -o program main.c

# BAD
gcc -o program main.c
```

### 2. **Silent Commands**:
```makefile
# @ suppresses command echo
@echo "Compiling..."        # Shows: Compiling...
@gcc -o program main.c      # Doesn't show command

# Without @
echo "Compiling..."         # Shows: echo "Compiling..."
                            #        Compiling...
```

### 3. **Proper Dependencies**:
```makefile
# GOOD - objects depend on headers
$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@

# BAD - missing dependencies
$(OBJDIR)/%.o: %.c
	$(CC) -c $< -o $@
```

### 4. **Use .PHONY**:
```makefile
# Prevents conflicts with files named 'clean', 'all', etc.
.PHONY: all clean fclean re
```

---

## 🚀 Advanced Example: Complete Project

```makefile
# **************************************************************************** #
#                               CONFIGURATION                                  #
# **************************************************************************** #

NAME        = webserver
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -std=c99 -pedantic
LDFLAGS     = -lpthread
RM          = rm -f

# **************************************************************************** #
#                                DIRECTORIES                                   #
# **************************************************************************** #

SRCDIR      = src
OBJDIR      = obj
INCDIR      = include
LIBDIR      = lib

# **************************************************************************** #
#                                  FILES                                       #
# **************************************************************************** #

SOURCES     = $(wildcard $(SRCDIR)/*.c) \
              $(wildcard $(SRCDIR)/*/*.c)

OBJECTS     = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
HEADERS     = $(wildcard $(INCDIR)/*.h)

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "🔗 Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)
	@echo "✅ $(NAME) created successfully!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	@echo "🔨 Compiling $<..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) -r $(OBJDIR)

fclean: clean
	@echo "🗑️  Removing $(NAME)..."
	@$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g -DDEBUG
debug: re

install: $(NAME)
	cp $(NAME) /usr/local/bin/

.PHONY: all clean fclean re debug install
```

---

## 📝 Quick Reference

| Function | Description | Example |
|----------|-------------|---------|
| `$(wildcard pattern)` | Find files matching pattern | `$(wildcard *.c)` |
| `$(filter pattern, list)` | Filter list by pattern | `$(filter %.c, $(FILES))` |
| `$(filter-out pattern, list)` | Remove matching items | `$(filter-out main.c, $(SOURCES))` |
| `$(dir names)` | Directory part | `$(dir src/main.c)` → `src/` |
| `$(notdir names)` | Filename part | `$(notdir src/main.c)` → `main.c` |
| `$(basename names)` | Remove suffix | `$(basename main.c)` → `main` |
| `$(suffix names)` | Get suffix | `$(suffix main.c)` → `.c` |

### Automatic Variables:
| Variable | Description |
|----------|-------------|
| `$@` | Target name |
| `$<` | First dependency |
| `$^` | All dependencies |
| `$?` | Dependencies newer than target |
| `$*` | Stem of pattern rule |

---

*This guide covers everything you need to write efficient, maintainable Makefiles for C/C++ projects. Start simple and gradually add complexity as your projects grow!*

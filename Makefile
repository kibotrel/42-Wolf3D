# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 22:15:45 by kibotrel          #+#    #+#              #
#    Updated: 2019/07/10 15:39:16 by kibotrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable's name (Can be changed)

NAME		= wolf3d

# All the directories needed to know where files should be (Can be changed)

ABSDIR		= $(shell pwd)
OBJDIR		= objs/
OBJSUBDIRS	= core usage parsing utils raycasting setup events maths hud
SRCDIR		= srcs/
LFTDIR		= libft/
LPNGDIR		= libpng/
LZDIR		= libpng/ZLIB/lib/
SDLDIR		= $(ABSDIR)/SDL2.0.9/
INCDIR		= ./incs/ ./libft/incs/ ./SDL2.0.9/include/ ./libpng/incs/

# Source files (Can be changed)

INCS		= incs/env.h incs/wolf3d.h

SRC			= core/main.c					core/hooks.c				\
			  core/events.c												\
			 															\
			  raycasting/raycast.c			raycasting/collisions.c		\
																		\
			  events/update_cam.c			events/movements.c			\
			  events/resize.c				events/teleport.c			\
			  events/fullscreen.c			events/mouse.c				\
																		\
			  setup/setup.c					setup/raycasting.c			\
			  setup/camera.c				setup/graphic.c				\
																		\
			  parsing/map.c												\
																		\
			  hud/hud.c						 hud/objects.c				\
			  hud/minimap.c												\
																		\
			  utils/clean.c					utils/parsing.c				\
			  utils/draw_line.c				utils/image.c				\
																		\
			  maths/maths.c												\
																		\
			  usage/usage.c

LFT			= ./libft/libft.a
LPNG		= ./libpng/libpng.a

# Some tricks in order to get the makefile doing his job the way I want (Can't be changed)

CSRC		= $(addprefix $(SRCDIR), $(SRC))
COBJ		= $(addprefix $(OBJDIR), $(OBJ))
SUBDIRS		= $(foreach dir, $(OBJSUBDIRS), $(OBJDIR)$(dir))
INCLUDES	= $(foreach include, $(INCDIR), -I$(include))

# How files should be compiled with set flags (Can be changed)

CC			= gcc
OBJ			= $(SRC:.c=.o)
LIBS		= -L$(LFTDIR) -lft  -L$(LPNGDIR) -lpng $(shell $(ABSDIR)/SDL2/bin/sdl2-config --libs) -L./$(LZDIR) -lz
CFLAGS		= $(INCLUDES) -Wall -Wextra -Werror -O3 -g

# Color codes

RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# Check if object directory exists, build libs and then the Project

all: $(SUBDIRS) $(NAME)

SDL2:
	@mkdir -p SDL2/
	@mkdir -p SDL2/build
	@cd SDL2/build; 									\
	$(SDLDIR)/configure --prefix $(ABSDIR)/SDL2;		\
	make -j; 											\
	make install 										\

$(NAME): SDL2 $(LFT) $(LPNG) $(OBJDIR) $(COBJ)
	@echo "$(YELLOW)\n      - Building $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(COBJ)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(SUBDIRS):
	@mkdir -p $(SUBDIRS)

# Redefinition of implicit compilation rule to prompt some colors and file names during the said compilation

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	@echo "$(YELLOW)      - Compiling :$(RESET)" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation rule for function library "libft"

$(LFT):
	@make -sC $(LFTDIR) -j

$(LPNG):
	@make -sC $(LPNGDIR) -j

# Deleting all .o files and then the directory where they were located

clean:
	@make -sC $(LFTDIR) clean
	@make -sC $(LPNGDIR) clean
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	@$(RM) $(COBJ)

# Deleting the executable after cleaning up all .o files

fclean: clean
	@make -sC $(LFTDIR) fclean
	@make -sC $(LPNGDIR) fclean
	@rm -rf SDL2
	@echo "$(GREEN)***   Deleting executable file from $(NAME)   ...   ***\n$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

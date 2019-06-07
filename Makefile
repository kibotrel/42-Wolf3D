# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 22:15:45 by kibotrel          #+#    #+#              #
#    Updated: 2019/06/07 12:10:41 by reda-con         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable's name (Can be changed)

NAME		= wolf3d

# All the directories needed to know where files should be (Can be changed)

OBJDIR		= objs/
OBJSUBDIRS	= core usage parsing utils raycasting setup events maths hud
SRCDIR		= srcs/
LFTDIR		= libft/

SDLDIR		= ./frameworks/SDL2.framework/lib/
SDLHEAD		= -I ./frameworks/SDL2.framework/Versions/A/Headers					\
				-I ./frameworks/SDL2_ttf.framework/Versions/A/Headers			\
				-I ./frameworks/SDL2_image.framework/Versions/A/Headers			\
				-I ./frameworks/SDL2_mixer.framework/Headers					\
				-I ./frameworks/SDL2_net.framework/Headers						\
				-F ./frameworks

FRAMEWORKS	= -F ./frameworks													\
			-rpath ./frameworks													\
			-framework OpenGL -framework AppKit -framework OpenCl				\
			-framework SDL2 -framework SDL2_ttf -framework SDL2_image			\
			-framework SDL2_mixer -framework SDL2_net

INCDIR		= ./incs/ ./libft/incs/ $(HOME)/Downloads/SDL2-2.0.3/include/

# Source files (Can be changed)

SRC			= core/main.c					core/hooks.c						\
			 																	\
			raycasting/raycast.c			raycasting/collisions.c				\
																				\
			events/update_cam.c			events/movements.c						\
			events/place_blocks.c			events/resize.c						\
			events/movements_calculs.c											\
																				\
			setup/setup.c					setup/raycasting.c					\
			setup/camera.c				setup/graphic.c							\
																				\
			parsing/map.c														\
																				\
			hud/hud.c						hud/minimap.c						\
																				\
			utils/clean.c					utils/parsing.c						\
			utils/image.c														\
																				\
			maths/maths.c														\
																				\
			usage/usage.c

LFT			= ./libft/libft.a

# Some tricks in order to get the makefile doing his job the way I want (Can't be changed)

CSRC		= $(addprefix $(SRCDIR), $(SRC))
COBJ		= $(addprefix $(OBJDIR), $(OBJ))
SUBDIRS		= $(foreach dir, $(OBJSUBDIRS), $(OBJDIR)$(dir))
INCLUDES	= $(foreach include, $(INCDIR), -I$(include))

# How files should be compiled with set flags (Can be changed)

CC			= gcc
OBJ			= $(SRC:.c=.o)
LIBS		= -L$(LFTDIR) -lft
CFLAGS		= $(INCLUDES) -Wall -Wextra -Werror

# Color codes

RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# Check if object directory exists, build libft and then the Project

all:  $(SUBDIRS) $(NAME)

$(NAME): $(LFT) $(OBJDIR) $(COBJ)
	@echo "$(YELLOW)\n      - Building $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@$(CC) $(CFLAGS) $(LIBS) $(FRAMEWORKS) -o $(NAME) $(COBJ) -O3 -Ofast -g
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(SUBDIRS):
	@mkdir -p $(SUBDIRS)

# Redefinition of implicit compilation rule to prompt some colors and file names during the said compilation

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "$(YELLOW)      - Compiling :$(RESET)" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation rule for function library "libft"

$(LFT):
	@make -sC $(LFTDIR) -j

# Deleting all .o files and then the directory where they were located

clean:
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	@rm -f $(COBJ)

# Deleting the executable after cleaning up all .o files

fclean: clean
	@make -sC $(LFTDIR) fclean
	@echo "$(GREEN)***   Deleting executable file from $(NAME)   ...   ***\n$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

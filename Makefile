NAME := minilibx
SOURCE := test_mlx.c
OBJECT := $(SOURCE:.c=.o)
UNAME := $(shell uname -s)
# LFTDIR := libft
# LFT := $(LFTDIR)/libft.a
MLXDIR := minilibx-linux
MLX := $(MLXDIR)/libmlx.a
ifeq ($(UNAME), Linux)
CFLAGS := -Wall -Wextra -Werror -I$(MLXDIR)
LDLIBS := -lXext -lX11 
else
CFLAGS := -Wall -Wextra -Werror -I$(MLXDIR) -I/usr/X11/include
LDFLAGS := -L/usr/X11/lib
LDLIBS := -lXext -lX11 -framework OpenGL -framework AppKit
endif

$(NAME): $(MLX) $(OBJECT)
ifeq ($(UNAME), Linux)
	$(LINK.o) $(OBJECT) $(LDLIBS) $(MLX)  -o $@
else
	$(LINK.o) $^ $(LDLIBS) -o $@
endif

$(LFT): | $(LFTDIR)
	$(MAKE) -C $(LFTDIR)

# $(LFTDIR):
# 	git clone https://github.com/liqsuq/libft

$(MLX): | $(MLXDIR)
	$(MAKE) -C $(MLXDIR)

$(MLXDIR):
	git clone https://github.com/42Paris/minilibx-linux

all: $(NAME)

clean:
	-$(MAKE) -C $(LFTDIR) clean
	-$(MAKE) -C $(MLXDIR) clean
	$(RM) $(OBJECT)

fclean: clean
	$(RM) -r $(LFTDIR)
	$(RM) -r $(MLXDIR)
	$(RM) $(NAME)

re: fclean all
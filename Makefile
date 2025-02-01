NAME        := minilibx

SOURCE      := test_mlx.c

OBJECT      := $(SOURCE:.c=.o)

UNAME       := $(shell uname -s)

MLXDIR      := minilibx-linux
MLX         := $(MLXDIR)/libmlx.a


LFTDIR      := libft
LFT         := $(LFTDIR)/libft.a
LFT_REPO    := https://github.com/Killua0615/libft.git

FTPRINTFDIR := ft_printf
FTPRINTF     := $(FTPRINTFDIR)/libftprintf.a
FTPRINTF_REPO:= https://github.com/Killua0615/ft_printf.git

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

ifeq ($(UNAME), Linux)
  CFLAGS  += -I$(MLXDIR)
  LDFLAGS :=
  LDLIBS   = -L$(MLXDIR) -lmlx -lXext -lX11

else ifeq ($(UNAME), Darwin)
  CFLAGS  += -I$(MLXDIR) -I/usr/X11/include
  LDFLAGS := -L/usr/X11/lib
  LDLIBS   = -L$(MLXDIR) -lmlx -lXext -lX11 -framework OpenGL -framework AppKit
endif

LDLIBS     += $(LFT) $(FTPRINTF)

all: $(NAME)

$(NAME): $(MLX) $(LFT) $(FTPRINTF) $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX): | $(MLXDIR)
	$(MAKE) -C $(MLXDIR)

$(MLXDIR):
	git clone https://github.com/42Paris/minilibx-linux $(MLXDIR)

$(LFT): | $(LFTDIR)
	$(MAKE) -C $(LFTDIR)

$(LFTDIR):
	git clone $(LFT_REPO) $(LFTDIR)

$(FTPRINTF): | $(FTPRINTFDIR)
	$(MAKE) -C $(FTPRINTFDIR)

$(FTPRINTFDIR):
	git clone $(FTPRINTF_REPO) $(FTPRINTFDIR)

clean:
	$(RM) $(OBJECT)
	-$(MAKE) -C $(MLXDIR) clean || true
	-$(MAKE) -C $(LFTDIR) clean || true
	-$(MAKE) -C $(FTPRINTFDIR) clean || true

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(MLXDIR)
	$(RM) -r $(LFTDIR)
	$(RM) -r $(FTPRINTFDIR)

re: fclean all

.PHONY: all clean fclean re

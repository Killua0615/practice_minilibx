#ifndef MINILIBX_H
#define MINILIBX_H

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <math.h>
#include "libft/libft.h"

#include "ft_printf/ft_printf.h"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

typedef struct s_point {
	int	x;
	int	y;
} t_point;

#endif // MINILIBX_H

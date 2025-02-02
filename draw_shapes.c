#include "minilibx.h"

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

#define WIDTH  800
#define HEIGHT 600

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr
		+ (y * data->line_length + (x * (data->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

static int	create_trgb(unsigned char a, unsigned char r,
						 unsigned char g, unsigned char b)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

static void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	steps;
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	abs_dx = (dx < 0) ? -dx : dx;
	int	abs_dy = (dy < 0) ? -dy : dy;
	float	x_inc, y_inc;
	float	x, y;

	steps = (abs_dx > abs_dy) ? abs_dx : abs_dy;
	if (steps == 0)
	{
		my_mlx_pixel_put(data, x0, y0, color);
		return ;
	}
	x_inc = (float)dx / (float)steps;
	y_inc = (float)dy / (float)steps;
	x = x0;
	y = y0;
	for (int i = 0; i <= steps; i++)
	{
		my_mlx_pixel_put(data, (int)(x + 0.5f), (int)(y + 0.5f), color);
		x += x_inc;
		y += y_inc;
	}
}

static void	draw_rectangle_outline(t_data *data, int sx, int sy, int w, int h, int color)
{
	draw_line(data, sx,     sy,     sx + w, sy,     color);
	draw_line(data, sx,     sy + h, sx + w, sy + h, color);
	draw_line(data, sx,     sy,     sx,     sy + h, color);
	draw_line(data, sx + w, sy,     sx + w, sy + h, color);
}

static void	draw_circle_outline(t_data *data, int cx, int cy, int r, int color)
{
	const int	segments = 360;
	float		theta_step = (2.0f * (float)M_PI) / (float)segments;
	float		prev_x = cx + r;
	float		prev_y = cy;

	for (int i = 1; i <= segments; i++)
	{
		float theta = theta_step * i;
		float new_x = cx + r * cosf(theta);
		float new_y = cy + r * sinf(theta);
		draw_line(data, (int)prev_x, (int)prev_y, (int)new_x, (int)new_y, color);
		prev_x = new_x;
		prev_y = new_y;
	}
}

static void	draw_polygon_outline(t_data *data, t_point *points, int n, int color)
{
	if (n < 2)
		return ;
	for (int i = 0; i < n - 1; i++)
	{
		draw_line(data,
			points[i].x,   points[i].y,
			points[i + 1].x, points[i + 1].y,
			color
		);
	}

	draw_line(data,
		points[n - 1].x, points[n - 1].y,
		points[0].x,     points[0].y,
		color
	);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_data	img;

	mlx = mlx_init();
	if (!mlx)
		exit(EXIT_FAILURE);

	win = mlx_new_window(mlx, WIDTH, HEIGHT, "Outline Shapes Only");
	if (!win)
		exit(EXIT_FAILURE);

	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img.img)
		exit(EXIT_FAILURE);

	img.addr = mlx_get_data_addr(img.img,
		&img.bits_per_pixel, &img.line_length, &img.endian);

	{
		int color_red = create_trgb(0, 255, 0, 0);
		draw_rectangle_outline(&img, 100, 100, 120, 80, color_red);
	}

  // 円
	{
		int color_green = create_trgb(0, 0, 255, 0);
		draw_circle_outline(&img, 350, 300, 80, color_green);
	}

	//三角形、ポリゴン描画
	{
		t_point tri[3] = {
			{550, 100},
			{500, 200},
			{600, 200}
		};
		int color_yellow = create_trgb(0, 255, 255, 0);
		draw_polygon_outline(&img, tri, 3, color_yellow);
	}

	//六角形
	{
		t_point hex[6];
		int	cx = 600;
		int	cy = 400;
		int	r = 50;
		for (int i = 0; i < 6; i++)
		{
			float theta = (2.0f * (float)M_PI) * ((float)i / 6.0f);
			hex[i].x = cx + (int)(r * cosf(theta));
			hex[i].y = cy + (int)(r * sinf(theta));
		}
		int color_blue = create_trgb(0, 0, 0, 255);
		draw_polygon_outline(&img, hex, 6, color_blue);
	}

	mlx_put_image_to_window(mlx, win, img.img, 0, 0);

	mlx_loop(mlx);
	return (0);
}

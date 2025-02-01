/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/01 13:40:22 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));

	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	if (!mlx)
	{
		fprintf(stderr, "Error: Failed to initialize MiniLibX.\n");
		return (EXIT_FAILURE);
	}

	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	if (!mlx_win)
	{
		fprintf(stderr, "Error: Failed to create window.\n");
		return (EXIT_FAILURE);
	}

	img.img = mlx_new_image(mlx, 500, 500);
	if (!img.img)
	{
		fprintf(stderr, "Error: Failed to create new image.\n");
		return (EXIT_FAILURE);
	}

	img.addr = mlx_get_data_addr(img.img,
								&img.bits_per_pixel,
								&img.line_length,
								&img.endian);

	my_mlx_pixel_put(&img, 10, 10, 0x0000FF00);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);

	return (EXIT_SUCCESS);
}
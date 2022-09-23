/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 01:27:38 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/23 14:21:07 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libmlx/mlx.h"
# include "../libmlx/improved_mlx.h"
# include "../libft/include/libft.h"
# include "parsing.h"
# include "keys.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# define PI 	3.1415926535
# define DR 	0.0174533

# define N		0
# define S		1
# define E		2
# define O		3
# define DOOR	4

typedef struct s_pos
{
	float		x;
	float		y;
	float		pdx;
	float		pdy;	
	float		pa;

	int			ipx;
	int			ipx_add_xo;
	int			ipx_sub_xo;
	int			ipy;
	int			ipy_add_yo;
	int			ipy_sub_yo;
	int			ipx_add_px;
	int			ipx_sub_px;
	int			ipy_add_py;
	int			ipy_sub_py;
	float		px;
	float		py;
	int			xo;
	int			yo;
}					t_pos;

typedef struct s_raycasting
{
	int			tmpdir1;
	int			tmpdir2;
	int			dir;

	int			focal;

	float		disv;
	float		dish;
	float		dist;

	float		lineh;
	float		lineo;

	float		atan;
	float		ntan;

	float		ra;
	float		rayx;
	float		rayy;
	float		vertx;
	float		verty;
	float		horix;
	float		horiy;
	float		xo;
	float		yo;
	float		ca;

	float		ratiox;
	float		shade;

	int			mp;
	int			mx;
	int			my;
	int			dow;
}					t_raycasting;

typedef struct s_image
{
	void		*img;
	char		*addr;
	u_int32_t	**arr;

	int			bits_per_pixel;
	int			line_length;
	int			endian;

	int			widt;
	int			heig;
}					t_image;

typedef struct cub
{
	void			*mlx;
	void			*mlxwin;

	int				*map;

	int				mapw;
	int				maph;
	int				mapscale;
	int				max;
	int				resizemap;

	int				checkimg;

	int				mouse_grabbed;
	int				display_map;

	char			clavier[7];

	t_raycasting	data;
	t_pos			pos;
	t_image			image[3];
	t_image			texture[5];
	t_parsed		*pars;
}					t_cub;

#endif

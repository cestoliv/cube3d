/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 01:27:38 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/12 15:16:53 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libmlx/mlx.h"
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>


# define PI 3.1415926535
# define PI2 PI / 2
# define PI3 3 * PI / 2

# define DR 0.0174533

# define N	0
# define S	1
# define E	2
# define O	3

typedef struct s_pos
{
	
	float		x;		// pose
	float		y;
	float		pdx;	// Delta x et y deplacement
	float		pdy;	
	float		pa;		//player angle

}					t_pos;


typedef struct s_raycasting
{
	int			tmpdir1;
	int			tmpdir2;
	int			dir;

	int			focal;
	
	float		disV;
	float		disH;
	float		disT;

	float		lineH;
	float		lineO;
	

	float		aTan;
	float		nTan;

	float		ra;
	float		rayX;
	float		rayY;
	float		vertx;
	float		verty;
	float		horix;
	float		horiy;
	float		xo;
	float		yo;
	float		ca;

	

}					t_raycasting;


typedef struct s_image
{
	
	void	*img;

	char	*addr;
	
	u_int32_t	**arr;
	
	int		bits_per_pixel; // for image
	int		line_length;
	int		endian;

	int		Widt; // for texture
	int		Heig;
	
}					t_image;


typedef struct cub
{
	void	*mlx;
	void	*mlxwin;

	int		map[91];


	int		mapW;
	int		mapH;
	int		mapScale;

	char 	clavier[6];

	t_raycasting	data;
	t_pos			pos;
	
	t_image		image[3];
	t_image		texture[4];
}					t_cub;




#endif

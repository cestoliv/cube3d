/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 01:14:36 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/15 16:04:33 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"
#include "parsing.h"

void	drawrays(t_cub *cub)
{
	cub->data.ra = cub->pos.pa - 0.0043633231 * (240 >> 1);
	fix_angle(cub);
	cub->data.focal = 0;
	while (cub->data.focal < 480)
	{
		reset_raycasting_varshori(cub);
		ft_hori(cub);
		ft_hori_try_contact(cub);
		reset_raycasting_varsverti(cub);
		ft_verti(cub);
		ft_verti_try_contact(cub);
		cub->data.shade = 1;
		ft_shorter(cub);
		ft_draw_line(cub, cub->pos, cub->data.rayX / cub->resizemap, \
			cub->data.rayY / cub->resizemap);
		cub->data.ratiox = (int)(cub->data.rayX / 2) % 32;
		ft_final_maths(cub);
		ft_drawwalls(cub, cub->data.focal * 4, \
			cub->data.lineO, cub->data.lineH);
		cub->data.ra += 0.0043633231 / 2;
		fix_angle(cub);
		cub->data.focal++;
	}
}

void	playerdir(t_cub *cub)
{
	if (cub->pars->player.dir == 'E')
		cub->pos.pa = 0;
	if (cub->pars->player.dir == 'W')
		cub->pos.pa = PI;
	if (cub->pars->player.dir == 'N')
		cub->pos.pa = - PI / 2;
	if (cub->pars->player.dir == 'S')
		cub->pos.pa = PI / 2;
}

void	init(t_cub *cub) // ajouter en argument structure olivier
{
	// ft_recuperation
	cub->mlx = mlx_init();
	cub->mlxwin = mlx_new_window(cub->mlx, 1920, 1080, "Cub3D");
	cub->pars->player.y += 1;
	playerdir(cub);
	cub->pos.pdx = cos(cub->pos.pa) * 5;
	cub->pos.pdy = sin(cub->pos.pa) * 5;
	cub->data.focal = 0;
	cub->mapW = cub->pars->map1D->width;		
	cub->mapH = cub->pars->map1D->height;
	if (cub->mapH > cub->mapW)
		cub->max = cub->mapH;
	else
		cub->max = cub->mapW;
	cub->resizemap = 2;
	if (cub->max > 25)
		cub->resizemap += 2;
	cub->pos.x = 64 * ((double)cub->pars->player.x + 0.5);					// a extraire
	cub->pos.y = 64 * ((double)cub->pars->player.y - 0.5);
	
	cub->mouse_grabbed = 0;

	cub->mapScale = 64;
	cub->map = cub->pars->map1D->map;
	cub->image[0].img = mlx_new_image(cub->mlx, 1920, 1080);
	cub->image[1].img = mlx_new_image(cub->mlx, 1920, 1080);
	cub->image[2].img = mlx_new_image(cub->mlx, 1920, 1080);
	init_imagespartone(cub);
	
	ft_bzero(cub->clavier, sizeof(char) * 7);
}

int	parse_only(t_parsed *pars)
{
	if (!pars)
		return (1);
	ft_printf("MAP OK.\n");
	free_parsed(pars);
	return (0);
}

int	mouse_motion(int x, int y, t_cub *cub)
{
	static int	prev_x = 560;
	float		rot;

	if (!cub->mouse_grabbed)
		return (0);
	rot = (prev_x - x) / (float)1000;
	if (rot < 0)
		rot *= -1;
	if (x > 960)
	{
		cub->pos.pa += rot;
		if (cub->pos.pa > 2 * PI)
			cub->pos.pa -= 2 * PI;
		cub->pos.pdx = cos(cub->pos.pa) * 5;
		cub->pos.pdy = sin(cub->pos.pa) * 5;
	}
	else if (x < 960)
	{
		cub->pos.pa -= rot;
		if (cub->pos.pa < 0)
			cub->pos.pa += 2 * PI;
		cub->pos.pdx = cos(cub->pos.pa) * 5;
		cub->pos.pdy = sin(cub->pos.pa) * 5;
	}
	mlx_mouse_move(cub->mlxwin, 960, 540);
	prev_x = x;
	return (0);
}

int	mouse_release(int key, int x, int y, void *param)
{
	t_cub	*cub;

	cub = param;
	if (key == MOUSE_LEFT)
	{
		if (cub->mouse_grabbed)
		{
			mlx_mouse_show();
			cub->mouse_grabbed = 0;
		}
		else
		{
			mlx_mouse_hide();
			mlx_mouse_move(cub->mlxwin, 960, 540);
			cub->mouse_grabbed = 1;
		}
	}
	return (0);
}

int	destroy(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_destroy_image(cub->mlx, cub->image[0].img);
	mlx_destroy_image(cub->mlx, cub->image[1].img);
	mlx_destroy_image(cub->mlx, cub->image[2].img);
	mlx_destroy_image(cub->mlx, cub->texture[0].img);
	mlx_destroy_image(cub->mlx, cub->texture[1].img);
	mlx_destroy_image(cub->mlx, cub->texture[2].img);
	mlx_destroy_image(cub->mlx, cub->texture[3].img);
	mlx_destroy_window(cub->mlx, cub->mlxwin);
	free_parsed(cub->pars);
	//sleep(60); //   sleep pour check leaks
	exit (0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc == 3 && !ft_strncmp("-p", argv[1], 2) && ft_strlen(argv[1]) == 2)
	{
		cub.pars = parse(argv[2]);
		return (parse_only(cub.pars));
	}
	else if (argc != 2)
	{
		ft_printf("Usage: ./cube3d [-p] <map path>\n");
		return(1);
	}
	
	cub.pars = parse(argv[1]);
	print_map(cub.pars);
	init(&cub);
	ft_draw_font(&cub);
	ft_drawmap(&cub);
	mlx_hook(cub.mlxwin, 2, 1L << 0, key_hook, &cub);
	mlx_hook(cub.mlxwin, 3, 2L << 0, key_hook_release, &cub);

	mlx_hook(cub.mlxwin, ON_DESTROY, 0L, destroy, &cub);
	mlx_hook(cub.mlxwin, ON_MOTION_NOTIFY, 0L, mouse_motion, &cub);
	//mlx_hook(cub.mlxwin, ON_BUTTON_PRESS, 0L, mouse_press, &cub);
	mlx_hook(cub.mlxwin, ON_BUTTON_RELEASE, 0L, mouse_release, &cub);

	mlx_loop_hook(cub.mlx, render_next_frame, &cub);
	mlx_loop(cub.mlx);
	free_parsed(cub.pars);
	return (0);
}

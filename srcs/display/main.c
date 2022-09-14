/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Romain <Romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 01:14:36 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/13 18:29:10 by Romain           ###   ########.fr       */
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
	mlx_loop_hook(cub.mlx, render_next_frame, &cub);
	mlx_loop(cub.mlx);
	free_parsed(cub.pars);
	return (0);
}

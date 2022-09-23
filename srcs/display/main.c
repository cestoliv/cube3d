/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 01:14:36 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/23 14:44:25 by ocartier         ###   ########.fr       */
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
		if (cub->display_map)
			ft_draw_line(cub, cub->pos, cub->data.rayx / cub->resizemap, \
				cub->data.rayy / cub->resizemap);
		cub->data.ratiox = (int)(cub->data.rayx / 2) % 32;
		ft_final_maths(cub);
		ft_drawwalls(cub, cub->data.focal * 4, \
			cub->data.lineo, cub->data.lineh);
		cub->data.ra += 0.0043633231 / 2;
		fix_angle(cub);
		cub->data.focal++;
	}
}

void	ft_recup(t_cub *cub)
{
	cub->pars->player.y += 1;
	cub->pos.pdx = cos(cub->pos.pa) * 5;
	cub->pos.pdy = sin(cub->pos.pa) * 5;
	cub->data.focal = 0;
	cub->mapw = cub->pars->map1d->width;
	cub->maph = cub->pars->map1d->height;
	cub->pos.x = 64 * ((double)cub->pars->player.x + 0.5);
	cub->pos.y = 64 * ((double)cub->pars->player.y - 0.5);
	cub->mouse_grabbed = 0;
	cub->display_map = 0;
	cub->mapscale = 64;
}

void	init(t_cub *cub)
{
	cub->checkimg = 0;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return ;
	cub->mlxwin = mlx_new_window(cub->mlx, 1920, 1080, "Cub3D");
	playerdir(cub);
	ft_recup(cub);
	if (cub->maph > cub->mapw)
		cub->max = cub->maph;
	else
		cub->max = cub->mapw;
	cub->resizemap = 2;
	if (cub->max > 25)
		cub->resizemap += 2;
	if (cub->max > 50)
		cub->resizemap += 2;
	if (cub->max > 100)
		cub->resizemap += 2;
	cub->map = cub->pars->map1d->map;
	init_imagespartone(cub, &cub->checkimg);
	ft_bzero(cub->clavier, sizeof(char) * 7);
	return ;
}

int	ft_errorimg(t_cub *cub, int i)
{
	mlx_ptr_t	*new_mlx;
	int			j;

	new_mlx = cub->mlx;
	j = 0;
	if (i == 0)
		return (0);
	while (j < i && j <= 2)
	{
		mlx_destroy_image(cub->mlx, cub->image[j].img);
		free(cub->image[j].arr);
		j++;
	}
	while (j < i)
	{
		mlx_destroy_image(cub->mlx, cub->texture[j - 3].img);
		free(cub->texture[j - 3].arr);
		j++;
	}
	mlx_destroy_image(cub->mlx, new_mlx->font);
	mlx_destroy_window(cub->mlx, cub->mlxwin);
	free(cub->mlx);
	free_parsed(cub->pars);
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
		return (ft_printf("Usage: ./cub3d [-p] <map path>\n"));
	cub.pars = parse(argv[1]);
	if (!cub.pars)
		return (1);
	init(&cub);
	if (cub.checkimg != 8)
		return (ft_errorimg(&cub, cub.checkimg));
	ft_draw_font(&cub);
	ft_drawmap(&cub);
	mlx_hook(cub.mlxwin, 2, 1L << 0, key_hook, &cub);
	mlx_hook(cub.mlxwin, 3, 2L << 0, key_hook_release, &cub);
	mlx_hook(cub.mlxwin, ON_DESTROY, 0L, destroy, &cub);
	mlx_hook(cub.mlxwin, ON_MOTION_NOTIFY, 0L, mouse_motion, &cub);
	mlx_hook(cub.mlxwin, ON_BUTTON_RELEASE, 0L, mouse_release, &cub);
	mlx_loop_hook(cub.mlx, render_next_frame, &cub);
	mlx_loop(cub.mlx);
	return (0);
}

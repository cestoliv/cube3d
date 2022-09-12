/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 01:14:36 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/12 15:10:26 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	drawrays(t_cub *cub)
{
	int mx,my,mp,dof;      // ra player angle temporaire ; aTan nTan

	int x;
	int y;

	x = 0;
	y = 0;

	cub->data.ra = cub->pos.pa - 0.0043633231 * (240 >> 1);

	if (cub->data.ra < 0)
		cub->data.ra += 2 * PI;
	if (cub->data.ra > 2 * PI)
		cub->data.ra -= 2 * PI;

	for (cub->data.focal = 0; cub->data.focal < 480; cub->data.focal++)
	{
	// P1
		dof = 0;
		cub->data.disH = 1000000;
		cub->data.horix = cub->pos.x;
		cub->data.horiy = cub->pos.y;
		cub->data.aTan = -1/tan(cub->data.ra);
		if (cub->data.ra > PI){
			cub->data.rayY = (((int)cub->pos.y>>6)<<6) - 0.0001;
			cub->data.rayX = (cub->pos.y - cub->data.rayY) * cub->data.aTan + cub->pos.x;
			cub->data.yo = -64;
			cub->data.xo = -cub->data.yo * cub->data.aTan;
			cub->data.tmpdir1 = N;// N
		}
		if (cub->data.ra < PI){
			cub->data.rayY = (((int)cub->pos.y>>6)<<6) + 64;
			cub->data.rayX = (cub->pos.y - cub->data.rayY) * cub->data.aTan + cub->pos.x;
			cub->data.yo = 64;
			cub->data.xo = -cub->data.yo * cub->data.aTan;
			cub->data.tmpdir1 = S;
		}
		if (cub->data.ra == 0 || cub->data.ra == PI)
		{
			cub->data.rayX = cub->pos.x;
			cub->data.rayY = cub->pos.y;
			dof = 16;
		}
		while (dof < 16)
		{
			mx = (int)(cub->data.rayX)>>6;
			my = (int)(cub->data.rayY)>>6;
			mp = my * cub->mapW + mx;
			if(mp > 0 && mp < cub->mapW * cub->mapH && cub->map[mp] == 1)
			{
				cub->data.horix = cub->data.rayX;
				cub->data.horiy = cub->data.rayY;
				cub->data.disH = dist(cub->pos.x, cub->pos.y, cub->data.horix, cub->data.horiy, cub->data.ra);
				dof=16;
			}//hit
			else
			{
				cub->data.rayX += cub->data.xo;
				cub->data.rayY += cub->data.yo;
				dof += 1;
			}
		}




	//P2
		dof = 0;
		cub->data.disV = 1000000;
		cub->data.vertx = cub->pos.x;
		cub->data.verty = cub->pos.y;
		cub->data.nTan = -tan(cub->data.ra);
		if (cub->data.ra > PI2 && cub->data.ra < PI3){
			cub->data.rayX = (((int)cub->pos.x>>6)<<6) - 0.0001;
			cub->data.rayY = (cub->pos.x - cub->data.rayX) * cub->data.nTan + cub->pos.y;
			cub->data.xo = -64;
			cub->data.yo = -cub->data.xo * cub->data.nTan;
			cub->data.tmpdir2 = O;// W
		}
		if (cub->data.ra < PI2 || cub->data.ra > PI3){
			cub->data.rayX = (((int)cub->pos.x>>6)<<6) + 64;
			cub->data.rayY = (cub->pos.x - cub->data.rayX) * cub->data.nTan + cub->pos.y;
			cub->data.xo = 64;
			cub->data.yo = -cub->data.xo * cub->data.nTan;
			cub->data.tmpdir2 = E;// E
		}
		if (cub->data.ra == 0 || cub->data.ra == PI)
		{
			cub->data.rayX = cub->pos.x;
			cub->data.rayY = cub->pos.y;
			dof = 16;
		}
		while (dof < 16)
		{
			mx=(int)(cub->data.rayX)>>6;
			my=(int)(cub->data.rayY)>>6;
			mp = my * cub->mapW + mx;
			if(mp > 0 && mp < cub->mapW * cub->mapH && cub->map[mp]==1)
			{
				cub->data.vertx = cub->data.rayX;
				cub->data.verty = cub->data.rayY;
				cub->data.disV = dist(cub->pos.x, cub->pos.y, cub->data.vertx, cub->data.verty, cub->data.ra);
				dof=16;
			}//hit
			else
			{
				cub->data.rayX += cub->data.xo;
				cub->data.rayY += cub->data.yo;
				dof+=1;
			}
		}

		float shade=1;

		if (cub->data.disV > cub->data.disH)
		{
			if (cub->data.tmpdir1 == N)
				cub->data.dir = N;
			else
				cub->data.dir = S;
			cub->data.rayX = cub->data.horix;
			cub->data.rayY = cub->data.horiy;
			cub->data.disT = cub->data.disH;
		}
		if (cub->data.disV < cub->data.disH)
		{
			if (cub->data.tmpdir2 == E)
				cub->data.dir = E;
			else
				cub->data.dir = O;
			shade = 0.5;
			cub->data.rayX = cub->data.vertx;
			cub->data.rayY = cub->data.verty;
			cub->data.disT = cub->data.disV;
		}

		ft_draw_line(&cub->image[0], cub->pos.x / 2 , cub->pos.y / 2 , cub->data.rayX / 2, cub->data.rayY / 2, 2); // ray on map

		cub->data.ca = cub->pos.pa - cub->data.ra;
		if (cub->data.ca < 0)
			cub->data.ca += 2 * PI;
		if (cub->data.ca > 2 * PI)
			cub->data.ca -= 2 * PI;
		cub->data.disT = cub->data.disT * cos(cub->data.ca) / 2;
		cub->data.lineH = (cub->mapScale * 340) / cub->data.disT;
		cub->data.lineO = 540;

		float tx = (int)(cub->data.rayX / 2 ) % 32;

		if(shade==1)
		{
			tx=(int)(cub->data.rayX / 2.0) % 32;
			if(cub->data.ra>180)
				tx=31-tx;
		}
		else
		{
			tx=(int)(cub->data.rayY / 2.0) % 32;
			if(cub->data.ra > 90 && cub->data.ra < 270)
				tx=31-tx;
		}

		ft_drawwalls(cub, cub->data.focal * 4, cub->data.lineO , cub->data.lineH, tx);

 		cub->data.ra += 0.0043633231 / 2;
		if (cub->data.ra < 0)
			cub->data.ra += 2 * PI;
		if (cub->data.ra > 2 * PI)
			cub->data.ra -= 2 * PI;
	}
}

int	render_next_frame(t_cub *cub)
{
	int x;
	int y;

	x = 0;
	y = 0;

	int xo=0; if(cub->pos.pdx<0){ xo=-20;} else{ xo=20;}                                    //x offset to check map
 	int yo=0; if(cub->pos.pdy<0){ yo=-20;} else{ yo=20;}                                    //y offset to check map
 	int ipx=cub->pos.x/64.0, ipx_add_xo=(cub->pos.x+xo)/64.0, ipx_sub_xo=(cub->pos.x-xo)/64.0;             //x position and offset
 	int ipy=cub->pos.y/64.0, ipy_add_yo=(cub->pos.y+yo)/64.0, ipy_sub_yo=(cub->pos.y-yo)/64.0;

	if (cub->clavier[0] == 1)
	{
		if(cub->map[ipy * cub->mapW        + ipx_add_xo]==0)
			cub->pos.x+=cub->pos.pdx;
 		if(cub->map[ipy_add_yo * cub->mapW + ipx       ]==0)
			 	cub->pos.y+=cub->pos.pdy;
	}
	if (cub->clavier[1] == 1)
	{
		cub->pos.pa += 0.05;
		if(cub->pos.pa > 2 * PI)
			cub->pos.pa -= 2 * PI;
		cub->pos.pdx = cos(cub->pos.pa) * 5;
		cub->pos.pdy = sin(cub->pos.pa) * 5;
	}
	if (cub->clavier[2] == 1)
	{

		if(cub->map[ipy * cub->mapW        + ipx_sub_xo]==0)
			cub->pos.x-=cub->pos.pdx;
 		if(cub->map[ipy_sub_yo * cub->mapW + ipx       ]==0)
			cub->pos.y-=cub->pos.pdy;

	}
	if (cub->clavier[3] == 1)
	{
		cub->pos.pa -= 0.05;
		if(cub->pos.pa < 0)
			cub->pos.pa += 2 * PI;
		cub->pos.pdx = cos(cub->pos.pa) * 5;
		cub->pos.pdy = sin(cub->pos.pa) * 5;
	}
	if (cub->pos.x > 1920)
		cub->pos.x = 0;
	if (cub->pos.x < 0)
		cub->pos.x = 1920;
	if (cub->pos.y > 1080)
		cub->pos.y = 0;
	if (cub->pos.y < 0)
		cub->pos.y = 1080;

	mlx_clear_window(cub->mlx, cub->mlxwin);

	drawrays(cub);

	mlx_put_image_to_window(cub->mlx, cub->mlxwin, cub->image[2].img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->mlxwin, cub->image[0].img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->mlxwin, cub->image[1].img, 0, 0);

	while (y < 1080)
	{
		int x = 0;
		while (x < 1920)
		{

				cub->image[0].arr[y][x++] = 0xff000000;

		}
		++y;
	}
	return (0);
};

int	key_hook_release(int keycode, t_cub *cub)  // direction et gauche droite
{
	if (keycode == 13)
	{
		cub->clavier[0] = 0;
	}
	if (keycode == 2)
	{
		cub->clavier[1] = 0;
	}
	if (keycode == 1)
	{
		cub->clavier[2] = 0;
	}
	if (keycode == 0)
	{
		cub->clavier[3] = 0;
	}
	if (cub->pos.x > 1920)
		cub->pos.x = 0;
	if (cub->pos.x < 0)
		cub->pos.x = 1920;
	if (cub->pos.y > 1080)
		cub->pos.y = 0;
	if (cub->pos.y < 0)
		cub->pos.y = 1080;
	return (0);
}

int	key_hook(int keycode, t_cub *cub)  // direction et gauche droite
{
	if (keycode == 53)
	{
		mlx_destroy_image(cub->mlx, cub->image[0].img);
		mlx_destroy_image(cub->mlx, cub->image[1].img);
		mlx_destroy_image(cub->mlx, cub->image[2].img);

		mlx_destroy_image(cub->mlx, cub->texture[0].img);
		mlx_destroy_image(cub->mlx, cub->texture[1].img);
		mlx_destroy_image(cub->mlx, cub->texture[2].img);
		mlx_destroy_image(cub->mlx, cub->texture[3].img);
		mlx_destroy_window(cub->mlx, cub->mlxwin);
	//	sleep(10);
		exit (0);
	}
	if (keycode == 13)
	{
		cub->clavier[0] = 1;
	}
	if (keycode == 2)
	{
		cub->clavier[1] = 1;
	}
	if (keycode == 1)
	{
		cub->clavier[2] = 1;
	}
	if (keycode == 0)
	{
		cub->clavier[3] = 1;
	}
	if (cub->pos.x > 1920)
		cub->pos.x = 0;
	if (cub->pos.x < 0)
		cub->pos.x = 1920;
	if (cub->pos.y > 1080)
		cub->pos.y = 0;
	if (cub->pos.y < 0)
		cub->pos.y = 1080;
	return (0);
}

void	init(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->mlxwin = mlx_new_window(cub->mlx, 1920, 1080, "Cub3D");

	cub->pos.x = 300;					// a extraire
	cub->pos.y = 300;
	cub->pos.pa = 0;
	cub->pos.pdx = cos(cub->pos.pa) * 5;
	cub->pos.pdy = sin(cub->pos.pa) * 5;
	cub->data.focal = 0;

	cub->mapW = 9;              		// a extraire
	cub->mapH = 9;
	cub->mapScale = 64;
	int	map[] =         //the map array. temporaire
	{
		1,1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,0,1,
		1,0,1,0,0,0,0,0,1,
		1,0,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,
	};
	int i = 0;
	while (i < 91){
		cub->map[i] = map[i];
		i++;
	}

	cub->image[0].img = mlx_new_image(cub->mlx, 1920, 1080);
	cub->image[1].img = mlx_new_image(cub->mlx, 1920, 1080);
	cub->image[2].img = mlx_new_image(cub->mlx, 1920, 1080);


	cub->image[0].addr = mlx_get_data_addr(cub->image[0].img, &cub->image[0].bits_per_pixel, &cub->image[0].line_length,
			&cub->image[0].endian);
	cub->image[0].arr = ft_mem2array((uint32_t*)cub->image[0].addr, 1920, 1080);


	cub->image[1].addr = mlx_get_data_addr(cub->image[1].img, &cub->image[1].bits_per_pixel, &cub->image[1].line_length,
			&cub->image[1].endian);
	cub->image[1].arr = ft_mem2array((uint32_t*)cub->image[1].addr, 1920, 1080);


	cub->image[2].addr = mlx_get_data_addr(cub->image[2].img, &cub->image[2].bits_per_pixel, &cub->image[2].line_length,
			&cub->image[2].endian);
	cub->image[2].arr = ft_mem2array((uint32_t*)cub->image[2].addr, 1920, 1080);


	cub->texture[0].img = mlx_xpm_file_to_image(cub->mlx, "1.xpm", &cub->texture[0].Widt, &cub->texture[0].Heig);
	cub->texture[0].addr = mlx_get_data_addr(cub->texture[0].img, &cub->texture[0].bits_per_pixel, &cub->texture[0].line_length,
			&cub->texture[0].endian);
	cub->texture[0].arr = ft_mem2array((uint32_t*)cub->texture[0].addr, cub->texture[0].Widt, cub->texture[0].Heig);

	cub->texture[1].img = mlx_xpm_file_to_image(cub->mlx, "wall_2.xpm", &cub->texture[1].Widt, &cub->texture[1].Heig);
	cub->texture[1].addr = mlx_get_data_addr(cub->texture[1].img, &cub->texture[1].bits_per_pixel, &cub->texture[1].line_length,
			&cub->texture[1].endian);
	cub->texture[1].arr = ft_mem2array((uint32_t*)cub->texture[1].addr, cub->texture[1].Widt, cub->texture[1].Heig);

	cub->texture[2].img = mlx_xpm_file_to_image(cub->mlx, "wall_3.xpm", &cub->texture[2].Widt, &cub->texture[2].Heig);
	cub->texture[2].addr = mlx_get_data_addr(cub->texture[2].img, &cub->texture[2].bits_per_pixel, &cub->texture[2].line_length,
			&cub->texture[2].endian);
	cub->texture[2].arr = ft_mem2array((uint32_t*)cub->texture[2].addr, cub->texture[2].Widt, cub->texture[2].Heig);

	cub->texture[3].img = mlx_xpm_file_to_image(cub->mlx, "wall_4.xpm", &cub->texture[3].Widt, &cub->texture[3].Heig);
	cub->texture[3].addr = mlx_get_data_addr(cub->texture[3].img, &cub->texture[3].bits_per_pixel, &cub->texture[3].line_length,
			&cub->texture[3].endian);
	cub->texture[3].arr = ft_mem2array((uint32_t*)cub->texture[3].addr, cub->texture[3].Widt, cub->texture[3].Heig);

	ft_bzero(cub->clavier, sizeof(char) * 7);

}

int main()
{
	t_cub	cub;

	init(&cub);
	ft_draw_font(&cub);
	ft_drawmap(&cub);
	mlx_hook(cub.mlxwin, 2, 1L<<0, key_hook, &cub);
	mlx_hook(cub.mlxwin, 3, 2L<<0, key_hook_release, &cub);
	mlx_loop_hook(cub.mlx, render_next_frame, &cub);
	mlx_loop(cub.mlx);
	return (0);
};

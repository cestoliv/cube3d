/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcuminal <rcuminal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:23:13 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/08 00:24:26 by rcuminal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "cub3d.h"

float		degToRad(int a);
float		dist(float ax, float ay, float bx, float by, float ang);
float		FixAng(float a);

void		my_mlx_pixel_put(t_image *image, int x, int y, int color);
void		ft_draw_line(t_image *data, int beginx, int beginy, int endx, int endy, int color);

void		ft_putplayer(uint32_t**	img_color, t_pos *pos);
void		ft_drawwalls(t_cub *cub, int beginx, int beginy, int lineH, float tx);
void		ft_drawsquare(uint32_t**	img_color, int posx, int posy, int scale, int color);
void		ft_drawmap(t_cub *cub);
void		ft_draw_font(t_cub *cub);

void		ft_freetabb(u_int32_t**tab);
void		ft_bzero(void *s, size_t n);
u_int32_t**	ft_mem2array(uint32_t *mem, size_t len_x, size_t len_y);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcuminal <rcuminal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:23:13 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/27 15:23:19 by rcuminal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "cub3d.h"

float		dist(float ax, float ay, float bx, float by);
void		ft_final_maths(t_cub *cub);
void		reset_raycasting_varshori(t_cub *cub);
void		reset_raycasting_varsverti(t_cub *cub);
void		fix_angle(t_cub *cub);

void		my_mlx_pixel_put(t_image *image, int x, int y, int color);
void		ft_draw_line(t_cub *cub, t_pos pos, int endx, int endy);

void		ft_putplayer(uint32_t **img_color, t_pos *pos);
void		ft_drawwalls(t_cub *cub, int beginx, int beginy, int lineH);
void		ft_drawsquare(uint32_t **img_color, int posx, int posy, int scale);
void		ft_drawmap(t_cub *cub);
void		ft_draw_font(t_cub *cub);

void		drawrays(t_cub *cub);

u_int32_t	**ft_mem2array(uint32_t *mem, size_t len_x, size_t len_y);
void		init_imagespartone(t_cub *cub, int *i);

void		ft_keyvalidation(t_cub *cub);
int			key_hook_release(int keycode, t_cub *cub);
int			key_hook(int keycode, t_cub *cub);
int			render_next_frame(t_cub *cub);
void		ft_hori(t_cub *cub);
void		ft_hori_try_contact(t_cub *cub);
void		ft_verti(t_cub *cub);
void		ft_verti_try_contact(t_cub *cub);
void		ft_shorter(t_cub *cub);
void		playerdir(t_cub *cub);
void		ft_setmovevalue(t_cub *cub);
void		ft_doormanager(t_cub *cub);
int			parse_only(t_parsed *pars);
int			mouse_motion(int x, int y, t_cub *cub);
int			mouse_release(int key, int x, int y, void *param);
int			destroy(void *param);
int			ft_errorimg_norm(t_cub *cub, int i, mlx_ptr_t *new_mlx);
int			ft_errorimg(t_cub *cub, int i);

#endif

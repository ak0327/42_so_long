/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q so_long");
}

static void	init_map_img(t_mlx_vars mlx, t_img *img)
{
	img->player_right1 = xpm_to_img_ptr(mlx, IMG_PLAYER_R1);
	img->player_right2 = xpm_to_img_ptr(mlx, IMG_PLAYER_R2);
	img->player_right3 = xpm_to_img_ptr(mlx, IMG_PLAYER_R3);
	img->player_right4 = xpm_to_img_ptr(mlx, IMG_PLAYER_R4);
	img->player_right5 = xpm_to_img_ptr(mlx, IMG_PLAYER_R5);
	img->player_left1 = xpm_to_img_ptr(mlx, IMG_PLAYER_L1);
	img->player_left2 = xpm_to_img_ptr(mlx, IMG_PLAYER_L2);
	img->player_left3 = xpm_to_img_ptr(mlx, IMG_PLAYER_L3);
	img->player_left4 = xpm_to_img_ptr(mlx, IMG_PLAYER_L4);
	img->player_left5 = xpm_to_img_ptr(mlx, IMG_PLAYER_L5);
	img->goal = xpm_to_img_ptr(mlx, IMG_GOAL);
	img->wall = xpm_to_img_ptr(mlx, IMG_WALL);
	img->item1 = xpm_to_img_ptr(mlx, IMG_ITEM_1);
	img->item2 = xpm_to_img_ptr(mlx, IMG_ITEM_2);
	img->empty1 = xpm_to_img_ptr(mlx, IMG_EMPTY_1);
	img->empty2 = xpm_to_img_ptr(mlx, IMG_EMPTY_2);
	img->empty3 = xpm_to_img_ptr(mlx, IMG_EMPTY_3);
	img->empty4 = xpm_to_img_ptr(mlx, IMG_EMPTY_4);
	if (null_check_for_map_img(img) == FAIL)
		error_exit("Img_ptr is NULL.");
}

static void	init_player(t_player *player, t_map_param map)
{
	player->pos_x = map.start_x;
	player->pos_y = map.start_y;
	player->next_x = (int)player->pos_x;
	player->next_y = (int)player->pos_y;
	player->cnt_step = 0;
	player->cnt_item = 0;
	player->can_exit = false;
	player->is_facing_right = true;
	player->flg_get_item = false;
}

static void	init_mlx_ptr(t_mlx_vars *mlx, t_map_param *m, t_img *i, t_player *p)
{
	const int	size_x = (int)m->size_x * IMAGE_SIZE;
	const int	size_y = (int)m->size_y * IMAGE_SIZE;

	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, size_x, size_y, "./so_long");
	mlx->map = m;
	mlx->img = i;
	mlx->player = p;
	init_map_img(*mlx, i);
	init_player(p, *m);
	mlx->is_game_end = false;
	mlx->animation_cnt = 0;
	mlx->player_flame = 0;
}

int	main(int argc, char *argv[])
{
	t_mlx_vars	mlx;
	t_map_param	map;
	t_img		img;
	t_player	player;
	char		*filepath;

	errno = 0;
	if (argc != 2)
		return (error_exit("[Invalid Arg] Cmd>$./so_long ./assets/map/<file>"));
	filepath = ft_strtrim(argv[1], IS_SPACE);
	if (!filepath)
		return (error_exit("Fail to get file path"));
	ft_printf("Read file: %s\n", filepath);
	if (read_and_valid_map(filepath, &map) == FAIL)
		return (error_exit("Invalid Map"));
	init_mlx_ptr(&mlx, &map, &img, &player);
	draw_game_screen(&mlx);
	ft_printf("[GAME START] There are %d items\n", map.cnt_item);
	mlx_hooks(&mlx);
	mlx_loop(mlx.mlx);
	mlx_destroys(&mlx);
	free(filepath);
	return (0);
}
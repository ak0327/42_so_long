/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static int	check_elems(t_map_param map, int **visited, int i, int j)
{
	int			k;
	int			path_to_goal;
	const int	d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	if (map.map_arr[i][j] == CHR_ITEM && visited[i][j] != 1)
		return (FAIL);
	path_to_goal = 0;
	if (map.map_arr[i][j] == CHR_GOAL)
	{
		k = 0;
		while (k < 4)
		{
			if ((0 < i + d[k][0]) && (i + d[k][0] < map.size_y - 1) && \
					(0 < j + d[k][1]) && (j + d[k][1] < map.size_x - 1) && \
					visited[i + d[k][0]][j + d[k][1]] == 1)
				path_to_goal++;
			k++;
		}
		if (path_to_goal == 0)
			return (FAIL);
	}
	return (PASS);
}

static int	check_path(t_map_param map, int **visited)
{
	int			i;
	int			j;

	i = 0;
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
		{
			if (check_elems(map, visited, i, j) == FAIL)
				return (FAIL);
			j++;
		}
		i++;
	}
	return (PASS);
}

static void	valid_path(t_map_param map)
{
	int		**visited;

	visited = create_visited(map.map_arr, (int)map.size_y, (int)map.size_x);
	if (!visited)
		error_exit("Fail to malloc in valid_path.");
	bfs(visited, map);
	if (check_path(map, visited) == FAIL)
		error_exit("No valid path in this map.");
	free_grid(visited, map.size_y);
}

int	valid_map(t_map_param *map)
{
	size_t			y;
	const size_t	size_y = map->size_y;
	const size_t	size_x = map->size_x;

	if (size_y < MAP_MIN || MAP_MAX < size_y)
		return (FAIL);
	if (size_x < MAP_MIN || MAP_MAX < size_x || size_y == size_x)
		return (FAIL);
	y = 0;
	while (y < size_y)
	{
		if (ft_strlen_ns(map->map_arr[y]) != size_x)
			return (FAIL);
		if (y == 0 || y == size_y - 1)
			if (cnt_chr_in_str(CHR_WALL, map->map_arr[y]) != size_x)
				return (FAIL);
		if (map->map_arr[y][0] != CHR_WALL)
			return (FAIL);
		if (map->map_arr[y][size_x - 1] != CHR_WALL)
			return (FAIL);
		y++;
	}
	valid_path(*map);
	return (PASS);
}

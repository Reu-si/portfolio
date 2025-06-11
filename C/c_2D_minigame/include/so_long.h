/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:34:31 by hreusing          #+#    #+#             */
/*   Updated: 2024/08/30 16:06:30 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define WIDTH 32
# define HEIGHT 32

# include "/home/hreusing/libft/libft.h"
# include "/home/hreusing/minilibx-linux/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_player
{
	void	*player;
}	t_player;

typedef struct s_textures
{
	void	*ground;
	void	*collectable;
	void	*exit;
	void	*wall;
	void	*enemy;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			ctrl_pressed;
	int			win;
	int			collectables;
	int			moves;
	int			width;
	int			height;
	int			x;
	int			y;
	int			map_rows;
	int			map_cols;
	int			exit_x;
	int			exit_y;
	int			flood_fill_collectable;
	int			current_frame;
	int			player_x;
	int			player_y;
	char		**map;
	t_textures	textures;
	t_player	player;
}	t_game;

void	error(char *message, t_game *game);
int		ft_get_map(char *map, t_game *game);
void	ft_fill_map(char *map, t_game *game, int lines);
int		ft_check_map(char *map, t_game *game, int linecount);
void	ft_check_rules(char *map, t_game *game);
void	check_filename(char	*filename, t_game *game);
int		check_walls(t_game *game);
int		check_lastrow(t_game *game);
int		check_elements(t_game *game);
int		check_chars(char *line, int *p, int *e, int *c);
int		find_valid_path(t_game *game);
void	set_positions(t_game *game);
void	flood_fill(t_game *game, int row, int col, char **visited);

void	ft_free_map(t_game *game);
void	ft_free_visited(char **visited, int rows);
void	ft_escape_game(t_game *game);
void	ft_game_won(t_game *game, int x);
int		close_window(t_game *game);

void	ft_open_images(t_game *game);
int		ft_get_assets(t_game *game);
void	ft_add_graphics(t_game *game);
void	ft_print_map(t_game *game, int i);
void	ft_load_image(t_game *game, void *texture, int x, int y);

void	ft_move_player(t_game *game, int move_x, int move_y);
int		key_hook(int keycode, t_game *game);
int		ft_valid_move(t_game *game, int x, int y);
void	ft_update_collectable(t_game *game, int new_x, int new_y);
void	ft_display_moves(t_game *game);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:54 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 16:36:34 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define ANTS		1
# define START		2
# define END		4

# define ASTART		1
# define AEND		2
# define PSTART		4
# define PEND		8
# define PIPE		16

typedef struct			s_fail
{
	struct s_fail		*next;
	int					id;
	char				pad[4];
}						t_fail;

typedef struct			s_blk_lst
{
	struct s_blk_lst	*next;
	int					id;
	char				pad[4];
}						t_blk_lst;

typedef struct			s_road
{
	char				*name;
	struct s_road		*next;
	t_fail				*f_road;
	size_t				size;
	int					state;
	int					col;
	int					nb_road;
	int					ant_now;
	int					ant_move;
	int					nb_ant;
	int					nb_cost;
	int					rep_ant;
	int					id_ants;
	int					count_ants;
	int					index;
	char				pad[4];
}						t_road;

typedef struct			s_file
{
	int					value;
	int					dist;
	struct s_file		*next;
}						t_file;

typedef struct			s_room
{
	char				*name;
	struct s_room		*next;
	int					pos;
	int					dist;
	int					status;
	int					x;
	int					y;
	int					start;
	int					end;
	int					road;
	int					print;
	char				pad[4];
}						t_room;

typedef struct			s_lst
{
	t_room				**tab;
	struct s_blk_lst	*blk;
	int					malloc_start;
	int					tmp_pos;
	int					cmp;
	int					pos_blk;
	int					pos_blk_f;
	int					nb_road;
	int					total_room;
	int					nb_best_move;
	int					nb_room;
	int					ret_bfs;
	int					cross;
	int					end;
	int					size_file;
	char				pad[4];
}						t_lst;

typedef struct			s_stock
{
	char				*room;
	char				*room1;
	struct s_stock		*next;
	int					x;
	int					y;
	int					start;
	int					end;
	int					pipe;
	int					com;
}						t_stock;

typedef struct			s_data
{
	t_road				**road;
	size_t				nb_ants;
	size_t				nb_room;
	int					**road_sol;
	int					line;
	int					tab_choose;
	int					print_st_ok;
	int					nb_ant_go;
	int					ant_finish;
	int					blk;
	int					nb_road_f;
	int					size_free;
	int					tmp_pos;
	int					flags;
	int					se;
	int					nb_con;
	int					start;
	int					end;
	int					nb_pos;
	int					total_road;
	int					total_cost;
	char				pad[4];
}						t_data;

int						lem_in(int ac, char **av);
int						parsing_map(t_data *env, t_stock **lst);
int						creat_maillon(t_stock **lst, char *name, char *x,
		char *y);
int						stock_pipe(t_data *env, t_lst **lst, t_stock *pipe);
int						add_flag(t_data *env, int flag);
int						check_nb_ants(char *str, t_data *env);
int						nb_split(char **tab);
int						check_valid_room(char *str, t_data *env,
		t_stock(**lst));
void					init_struct(t_data *env, int ac, char **av);
void					free_stock(t_stock **lst);
void					free_lst_adja(t_lst **lst, t_data *env);
void					free_road_adja(t_data *env, int val);
t_stock					*creat_maillon_stock(void);
t_lst					*creat_adja_lst(t_stock **room, t_data *env, size_t i);
t_lst					*parsing_main(t_data *env);
size_t					ft_lstsize_stock(t_stock **room);
size_t					ft_lstsize_room(t_room **room);
int						ft_lstsize_road(t_road **room);
int						check_name(t_data *env, t_lst **lst);
int						verif_pos(t_stock **lst);
int						algo_main(t_lst **lst, t_data *env);
int						bfs(t_data *env, t_lst **lst, t_file *tmp);
int						bfs_best(t_data *env, t_lst **lst, t_file *tmp);
void					free_file(t_file **file);
int						best_road(t_lst **lst, t_data *env);
int						other_road(t_lst **lst, t_data *env, int i);
int						verif_size_ant(char *ants);
void					del_first_file(t_file **file);
void					clean_status(t_lst **lst);
void					clean_dist(t_lst **lst);
int						change_road_bfs(t_lst **lst, int road, t_data *env);
void					reboot_nb_road(t_lst **lst);
int						stock_road(t_lst **lst, t_data *env);
void					free_blk_lst(t_blk_lst **blk);
int						stock_road_other(t_lst **lst, t_data *env);
int						creat_road(t_data *env);
int						stock_start_end(t_lst **lst, t_data *env);
int						find_nb_pos(t_lst **lst, t_data *env);
int						verif_back(t_lst **lst, int pos_blk, int i, int flag);
int						ants_treat(t_data *env, int id);
int						check_cross(t_lst **lst, t_file **file, int i,
		t_data *env);
int						add_file(t_lst **lst, t_file **file, int val,
		int dis);
int						treat_better(t_data *env, const int limit,
							const int id) __attribute__((const));
void					print_res(t_data *env, int i, int nb_line, int nb_max);
void					reboot_print(t_lst **lst);
int						sort_road(t_data *env, int i);
int						choose_road(t_data *env);
void					verif_if_one_pipe(t_lst **lst, t_data *env);
int						find_nb_max(t_data *env);
int						stock_it(t_lst **lst, t_data *env, int pos, int i);
void					check_valid_room_bis(t_data *env, t_stock **lst);
int						check_maillon_bis(char **tab);
int						rework_for_best(t_data *env);
int						choose_road_use(t_data *env);
void					nb_ant_road(t_data *env, int i);
void					free_road_sol(t_data *env);
void					free_fail_road(t_data *env);
int						solve_cross(t_data *env, int i, int j, t_road *nex);
int						find_id(t_data *env, int i, int j);
int						mark_fail(t_data *env, int i, int j);

#endif

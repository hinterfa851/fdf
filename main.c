#include <stdio.h>
#include "fdf.h"
#include "../../Downloads/minilibx_macos/mlx.h"
#include "libft/ft_strsplit.c"
#include "libft/ft_wordcount.c"
#include "libft/ft_freesher.c"
#include "libft/ft_atoi.c"
#include "alg.c"
#include "reader.c"
#include "to_iso.c"

int closer(void *param)
{
	(void)param;
	exit(0);
}

void rot_x(void *param)
{
	double m1[3][3] =
		    {
					{1, 0, 0},
					{0, cos(0.1), -sin(0.1)},
					{0, sin(0.1), cos(0.1)}
			};

	((b_list *)param)->coef_arr = mlpl_mtrx(((b_list *)param)->coef_arr, m1);
	mlx_clear_window(((b_list *)param)->conn_id, ((b_list *)param)->win_id);
	to_iso((b_list *)param, ((b_list *)param)->coef_arr);
}

void rot_y(void *param)
{
	double m2[3][3] =
			{
					{cos(0.1), 0, -sin(0.1)},
					{0, 1, 0},
					{sin(0.1), 0, cos(0.1)}
			};

	((b_list *)param)->coef_arr = mlpl_mtrx(((b_list *)param)->coef_arr, m2);
	mlx_clear_window(((b_list *)param)->conn_id, ((b_list *)param)->win_id);
	to_iso((b_list *)param, ((b_list *)param)->coef_arr);
}

void rot_z(void *param)
{
	double m3[3][3] =
			{
					{cos(0.1), -sin(0.1), 0},
					{sin(0.1), cos(0.1), 0},
					{0, 0, 1}
			};

	((b_list *)param)->coef_arr = mlpl_mtrx(((b_list *)param)->coef_arr, m3);
	mlx_clear_window(((b_list *)param)->conn_id, ((b_list *)param)->win_id);
	to_iso((b_list *)param, ((b_list *)param)->coef_arr);
}

int deal_key(int key, void *param)
{
	if (key == 0)
		rot_x(param);
	if (key == 1)
		rot_y(param);
	if (key == 2)
		rot_z(param);
	if (key == 53)
		closer((void *)param);
	return (0);
}

double **init_arr(void *everything)
{
	double **coef_arr;
	double m1[3][3] =
			{
					{1, 0, 0},
					{0, cos(INIT_A), sin(INIT_A)},
					{0, -sin(INIT_A), cos(INIT_A)}
			};
	double m3[3][3] =
			{
					{cos(INIT_B), -sin(INIT_B), 0},
					{sin(INIT_B), cos(INIT_B), 0},
					{0, 0, 1}
			};

	coef_arr = mlpl_mtrx2(m1, m3);
	to_iso((b_list *)everything, coef_arr);
	return coef_arr;
}


int main(int argc, char **argv)
{
	void *win_id;
	void *conn_id;
	b_list *wraper;
	int **arr;

	if (argc != 2)
	{
		printf("ATTENTION!!!!!!\n");
		return (0);
	}
	wraper = malloc(sizeof(b_list));
	conn_id = mlx_init();
	win_id = mlx_new_window(conn_id, WHIDTH, HIDHT, "FDF");
	(*wraper).win_id = win_id;
	(*wraper).issues = reader(argv[1]);
	(*wraper).conn_id = conn_id;
	(*wraper).coef_arr = init_arr((void *) wraper);
	mlx_hook(win_id, 2, 0, deal_key,(void *)wraper);
	mlx_hook(win_id, 17, 0, closer,(void *)0);
	mlx_loop(conn_id);
	return (0);
}
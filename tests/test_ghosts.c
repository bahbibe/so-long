/* Unit tests for the ghost logic (no window needed).
   Build and run with `make unit`. */

#include "so_long.h"
#include <stdio.h>

static int	g_fails;

#define CHECK(cond, name) do { \
	if (cond) printf("ok   %s\n", name); \
	else { printf("FAIL %s\n", name); g_fails++; } } while (0)

/* Build a t_game from a NULL terminated array of rows. Like the real game,
   it finds P and turns G into ghosts through init_ghosts(). */
static int	load(t_game *g, char **rows)
{
	int	i;
	int	j;

	ft_bzero(g, sizeof(*g));
	while (rows[g->lines])
		g->lines++;
	g->map = ft_calloc(g->lines + 1, sizeof(char *));
	i = -1;
	while (++i < g->lines)
		g->map[i] = ft_strdup(rows[i]);
	g->len = ft_line_len(g->map[0]);
	i = -1;
	while (++i < g->lines)
	{
		j = -1;
		while (++j < g->len)
		{
			if (g->map[i][j] == 'P')
			{
				g->pos_x = i;
				g->pos_y = j;
			}
		}
	}
	return (init_ghosts(g));
}

static void	unload(t_game *g)
{
	to_free(g->map);
	free_ghosts(g);
}

static void	test_init(void)
{
	t_game	g;
	char	*rows[] = {"11111", "1PG01", "1G0E1", "11111", NULL};
	int		i;
	int		j;
	int		left;

	CHECK(load(&g, rows) == 0, "init_ghosts succeeds");
	CHECK(g.ghost_count == 2, "init_ghosts counts 2 ghosts");
	CHECK(ghost_at(&g, 1, 2) && ghost_at(&g, 2, 1), "ghosts sit on their G cells");
	CHECK(!ghost_at(&g, 1, 1) && !ghost_at(&g, 0, 0), "ghost_at is false elsewhere");
	left = 0;
	i = -1;
	while (g.map[++i])
	{
		j = -1;
		while (g.map[i][++j])
			left += g.map[i][j] == 'G';
	}
	CHECK(left == 0, "G is removed from the map");
	unload(&g);
}

static void	test_chase(void)
{
	t_game	g;
	char	*rows[] = {"1111111", "1P1G001", "1010101", "1000101", "1111111",
		NULL};
	int		steps;
	int		caught;

	load(&g, rows);
	steps = 0;
	caught = 0;
	while (!caught && steps < 20)
	{
		caught = move_ghosts(&g);
		steps++;
	}
	CHECK(caught == 1, "ghost walks around a wall and catches the player");
	CHECK(steps == 6, "ghost takes the shortest path (6 steps)");
	CHECK(g.ghosts[0].x == g.pos_x && g.ghosts[0].y == g.pos_y,
		"caught ghost stands on the player");
	unload(&g);
}

static void	test_follows_player(void)
{
	t_game	g;
	char	*rows[] = {"11111111", "1P0000G1", "11111111", NULL};

	load(&g, rows);
	move_ghosts(&g);
	CHECK(g.ghosts[0].y == 5, "ghost moves one tile toward the player");
	g.pos_y = 3;
	CHECK(move_ghosts(&g) == 0 && g.ghosts[0].y == 4,
		"ghost follows a player that moved");
	CHECK(move_ghosts(&g) == 1, "ghost one tile away catches the player");
	unload(&g);
}

static void	test_no_stacking(void)
{
	t_game	g;
	char	*rows[] = {"11111", "1P0GG1", "11111", NULL};
	int		i;

	load(&g, rows);
	i = 0;
	while (i++ < 3)
		move_ghosts(&g);
	CHECK(g.ghosts[0].x != g.ghosts[1].x || g.ghosts[0].y != g.ghosts[1].y,
		"two ghosts never share a tile");
	unload(&g);
}

static void	test_unreachable(void)
{
	t_game	g;
	char	*rows[] = {"11111", "1P1G1", "11111", NULL};
	int		i;

	load(&g, rows);
	i = 0;
	while (i++ < 5)
		CHECK(move_ghosts(&g) == 0, "walled off ghost never catches");
	CHECK(g.ghosts[0].x == 1 && g.ghosts[0].y == 3,
		"walled off ghost stays where it is");
	unload(&g);
}

static void	test_no_ghosts(void)
{
	t_game	g;
	char	*rows[] = {"11111", "1P0C1", "11111", NULL};

	CHECK(load(&g, rows) == 0, "map without ghosts loads");
	CHECK(g.ghost_count == 0 && !g.ghosts && !g.dist && !g.queue,
		"no allocation without ghosts");
	CHECK(move_ghosts(&g) == 0, "move_ghosts is a no-op without ghosts");
	CHECK(!ghost_at(&g, 1, 1), "ghost_at is false without ghosts");
	free_ghosts(&g);
	free_ghosts(&g);
	CHECK(1, "free_ghosts is safe to call twice");
	unload(&g);
}

static void	test_missing_buffers(void)
{
	t_game	g;
	char	*rows[] = {"11111", "1P0G1", "11111", NULL};

	load(&g, rows);
	free(g.dist);
	g.dist = NULL;
	CHECK(move_ghosts(&g) == 0, "move_ghosts survives a missing dist buffer");
	free(g.queue);
	g.queue = NULL;
	CHECK(move_ghosts(&g) == 0, "move_ghosts survives a missing queue buffer");
	unload(&g);
}

int	main(void)
{
	test_init();
	test_chase();
	test_follows_player();
	test_no_stacking();
	test_unreachable();
	test_no_ghosts();
	test_missing_buffers();
	if (g_fails)
		printf("%d test(s) failed\n", g_fails);
	else
		printf("all ghost tests passed\n");
	return (g_fails != 0);
}

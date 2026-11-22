/* Unit tests for the pixel drawing code (no window needed).
   Build and run with `make unit`. Set DUMP=file.ppm to save a sample scene. */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>

static int	g_fails;

#define CHECK(cond, name) do { \
	if (cond) printf("ok   %s\n", name); \
	else { printf("FAIL %s\n", name); g_fails++; } } while (0)
#define PAD 64

/* A w x h frame inside a bigger zeroed buffer. Everything outside the frame
   is the guard area: any write there is a bug. */
static unsigned int	*make_frame(t_frame *f, int w, int h)
{
	unsigned int	*raw;

	raw = ft_calloc((w + 2 * PAD) * (h + 2 * PAD), 4);
	ft_bzero(f, sizeof(*f));
	f->addr = (char *)(raw + PAD * (w + 2 * PAD) + PAD);
	f->w = w;
	f->h = h;
	f->line = (w + 2 * PAD) * 4;
	f->bpp = 32;
	return (raw);
}

static int	guard_clean(unsigned int *raw, int w, int h)
{
	int	x;
	int	y;

	y = -1;
	while (++y < h + 2 * PAD)
	{
		x = -1;
		while (++x < w + 2 * PAD)
		{
			if ((x < PAD || y < PAD || x >= PAD + w || y >= PAD + h)
				&& raw[y * (w + 2 * PAD) + x])
				return (0);
		}
	}
	return (1);
}

static int	painted(t_frame *f, t_rect r)
{
	int	x;
	int	y;
	int	n;

	n = 0;
	y = r.y - 1;
	while (++y < r.y + r.h)
	{
		x = r.x - 1;
		while (++x < r.x + r.w)
			n += *(unsigned int *)(f->addr + y * f->line + x * 4) != 0;
	}
	return (n);
}

static void	test_shapes(void)
{
	t_frame			f;
	unsigned int	*raw;
	t_frame			bad;

	raw = make_frame(&f, 40, 30);
	put_px(&f, -1, 0, 1);
	put_px(&f, 0, -1, 1);
	put_px(&f, 40, 0, 1);
	put_px(&f, 0, 30, 1);
	put_px(NULL, 0, 0, 1);
	ft_bzero(&bad, sizeof(bad));
	put_px(&bad, 0, 0, 1);
	bad = f;
	bad.bpp = 24;
	put_px(&bad, 0, 0, 1);
	CHECK(painted(&f, (t_rect){0, 0, 40, 30}) == 0 && guard_clean(raw, 40, 30),
		"put_px ignores NULL, NULL addr, bad bpp and out of range");
	put_px(&f, 39, 29, 0xABCDEF);
	CHECK(painted(&f, (t_rect){39, 29, 1, 1}) == 1, "put_px writes inside");
	fill_rect(&f, (t_rect){-10, -10, 25, 25}, 5);
	CHECK(painted(&f, (t_rect){0, 0, 15, 15}) == 225 && guard_clean(raw, 40, 30),
		"fill_rect clips at the top left");
	fill_rect(&f, (t_rect){30, 20, 100, 100}, 5);
	CHECK(guard_clean(raw, 40, 30), "fill_rect clips at the bottom right");
	fill_rect(NULL, (t_rect){0, 0, 5, 5}, 5);
	fill_circle(NULL, (t_pt){0, 0}, 5, 5);
	dim_rect(NULL, (t_rect){0, 0, 5, 5}, 1);
	dim_rect(&f, (t_rect){-20, -20, 100, 100}, 1);
	CHECK(guard_clean(raw, 40, 30), "dim_rect clips and ignores NULL");
	free(raw);
	raw = make_frame(&f, 40, 30);
	fill_circle(&f, (t_pt){20, 15}, 8, 7);
	CHECK(painted(&f, (t_rect){20, 15, 1, 1}) && !painted(&f, (t_rect){0, 0, 4, 4})
		&& !painted(&f, (t_rect){20, 24, 1, 1}), "fill_circle fills a disc");
	fill_circle(&f, (t_pt){0, 0}, 20, 7);
	CHECK(guard_clean(raw, 40, 30), "fill_circle clips at the border");
	CHECK(shade(0x102030, 300) == 0xFFFFFF && shade(0x102030, -300) == 0
		&& shade(0x102030, 1) == 0x112131, "shade clamps each channel");
	free(raw);
}

static void	test_sprites(void)
{
	t_frame			f;
	unsigned int	*raw;
	t_pt			o;
	int				d;

	raw = make_frame(&f, 3 * TILE, 3 * TILE);
	o = (t_pt){TILE, TILE};
	draw_floor(&f, o, 0);
	draw_floor(&f, (t_pt){2 * TILE, TILE}, 1);
	draw_wall(&f, (t_pt){0, TILE}, 3);
	CHECK(painted(&f, (t_rect){0, TILE, 3 * TILE, TILE}) == 3 * TILE * TILE
		&& guard_clean(raw, 3 * TILE, 3 * TILE),
		"floor and wall paint every pixel of their tile and nothing else");
	free(raw);
	raw = make_frame(&f, 3 * TILE, 3 * TILE);
	draw_coin(&f, o, 0);
	draw_door(&f, (t_pt){0, 0}, 0);
	draw_door(&f, (t_pt){2 * TILE, 0}, 1);
	CHECK(painted(&f, (t_rect){o.x + 20, o.y + 20, 8, 8}) == 64
		&& painted(&f, (t_rect){0, 0, TILE, TILE}) > 500
		&& painted(&f, (t_rect){2 * TILE, 0, TILE, TILE}) > 500
		&& guard_clean(raw, 3 * TILE, 3 * TILE),
		"coin and both doors draw inside their tile");
	free(raw);
	raw = make_frame(&f, 3 * TILE, 3 * TILE);
	d = -1;
	while (++d < 8)
		draw_player(&f, o, d, -8 + d);
	draw_ghost(&f, o, (t_pt){-1, 1}, 5);
	CHECK(painted(&f, (t_rect){o.x + 20, o.y + 20, 8, 8}) == 64
		&& guard_clean(raw, 3 * TILE, 3 * TILE),
		"player (all facings) and ghost stay inside their tile");
	draw_player(&f, (t_pt){-30, -30}, 0, 0);
	draw_ghost(&f, (t_pt){3 * TILE - 10, 3 * TILE - 10}, (t_pt){0, 0}, 0);
	draw_coin(&f, (t_pt){-20, 3 * TILE - 5}, 2);
	CHECK(guard_clean(raw, 3 * TILE, 3 * TILE),
		"sprites half outside the frame are clipped");
	free(raw);
}

static void	test_numbers(void)
{
	t_frame			f;
	unsigned int	*raw;

	raw = make_frame(&f, 100, 20);
	draw_number(&f, (t_pt){0, 0}, 0, 1);
	CHECK(painted(&f, (t_rect){0, 0, 9, 15}) > 0
		&& !painted(&f, (t_rect){12, 0, 88, 20}), "draw_number(0) draws one digit");
	free(raw);
	raw = make_frame(&f, 100, 20);
	draw_number(&f, (t_pt){0, 0}, 1234, 1);
	CHECK(painted(&f, (t_rect){36, 0, 9, 15}) > 0
		&& !painted(&f, (t_rect){48, 0, 52, 20}), "draw_number(1234) draws 4 digits");
	draw_number(&f, (t_pt){0, 0}, -5, 2);
	draw_number(&f, (t_pt){90, 10}, 2147483647, 2);
	CHECK(guard_clean(raw, 100, 20), "draw_number ignores negatives and clips");
	free(raw);
}

static void	test_lerp(void)
{
	CHECK(lerp(10, 20, -5, 100) == 10 && lerp(10, 20, 0, 100) == 10
		&& lerp(10, 20, 50, 100) == 15 && lerp(10, 20, 999, 100) == 20
		&& lerp(20, 10, 50, 100) == 15, "lerp clamps and interpolates");
}

static void	dump(t_frame *f, char *path)
{
	FILE	*out;
	int		x;
	int		y;
	int		c;

	out = fopen(path, "wb");
	if (!out)
		return ;
	fprintf(out, "P6\n%d %d\n255\n", f->w, f->h);
	y = -1;
	while (++y < f->h)
	{
		x = -1;
		while (++x < f->w)
		{
			c = *(unsigned int *)(f->addr + y * f->line + x * 4);
			fputc(c >> 16 & 255, out);
			fputc(c >> 8 & 255, out);
			fputc(c & 255, out);
		}
	}
	fclose(out);
}

/* A small scene through the same helpers the game uses. */
static void	test_scene(char *dump_path)
{
	t_game			g;
	unsigned int	*raw;
	unsigned int	*raw2;
	char			*rows[] = {"1111111", "1P0C0E1", "10G0101", "1C0G0C1",
		"1111111", NULL};
	int				i;

	ft_bzero(&g, sizeof(g));
	g.lines = 5;
	g.len = 7;
	g.map = ft_calloc(6, sizeof(char *));
	i = -1;
	while (++i < 5)
		g.map[i] = ft_strdup(rows[i]);
	raw = make_frame(&g.fb, 7 * TILE, 5 * TILE + HUD_H);
	raw2 = make_frame(&g.bg, 7 * TILE, 5 * TILE + HUD_H);
	g.colct = 3;
	g.moves = 42;
	g.pos_x = 1;
	g.pos_y = 1;
	g.from = tile_origin(1, 1);
	g.ghost_count = 2;
	g.ghosts = ft_calloc(2, sizeof(t_ghost));
	g.ghosts[0] = (t_ghost){2, 2, 2, 2};
	g.ghosts[1] = (t_ghost){3, 3, 3, 3};
	build_bg(&g);
	i = -1;
	while (++i < g.bg.h)
		ft_memcpy(g.fb.addr + i * g.fb.line, g.bg.addr + i * g.bg.line,
			g.bg.w * 4);
	draw_items(&g, 0);
	draw_ghosts(&g, 100000);
	draw_player(&g.fb, tile_origin(1, 1), 3, 0);
	draw_hud(&g);
	CHECK(painted(&g.fb, (t_rect){0, 0, g.fb.w, g.fb.h}) == g.fb.w * g.fb.h
		&& guard_clean(raw, g.fb.w, g.fb.h), "sample scene fills the frame");
	if (dump_path)
		dump(&g.fb, dump_path);
	g.end = 2;
	draw_end(&g);
	CHECK(guard_clean(raw, g.fb.w, g.fb.h), "end panel stays inside the frame");
	to_free(g.map);
	free(g.ghosts);
	free(raw);
	free(raw2);
}

int	main(void)
{
	test_shapes();
	test_sprites();
	test_numbers();
	test_lerp();
	test_scene(getenv("DUMP"));
	if (g_fails)
	{
		printf("%d render test(s) failed\n", g_fails);
		return (1);
	}
	printf("all render tests passed\n");
	return (0);
}

# How it works

## Frame

There are no image files. `build_bg()` draws the walls and floor once into a background buffer. Each frame then does this:

1. `memcpy` the background into the frame buffer (about 1.9 MB for `map1`, which is 1296 x 368 px).
2. Draw the door, coins, ghosts and player on top, with positions interpolated between tiles.
3. Draw the top bar with a 3x5 bitmap digit font.
4. One `mlx_put_image_to_window`.

The old version cleared the window and called `put_image` for every tile, which flickered. The drawing code takes a plain `t_frame` (pointer, width, height, line size), not an MLX handle. That is why `tests/test_render.c` can run it on a `calloc`ed buffer with no display.

## Loop

`tick()` runs on every MLX loop iteration. It sleeps 5 ms if less than 16 ms passed since the last frame. It draws only when something changed: the state is dirty, the player or a ghost is moving, or the coin and ghost animation phase ticked (every 140 ms). On a map with one idle ghost this takes about 3% of one core. Redrawing every frame took about 8%.

## Ghosts

On each ghost step, `ghost_dist()` runs a BFS from the player over the map and stores the distance of every tile. Each ghost then moves to a neighbour whose distance is one less than its own, skipping tiles that already hold a ghost. A ghost with no path (distance -1) stays where it is.

The field only depends on the player position and the walls, so it is recomputed only when the player's tile changes.

## Map check

`check_path()` copies the map and floods it from `P` with a BFS and a heap queue of `lines * len` cells. A cell is queued at most once, so the queue cannot overflow. `E` is marked as reached but not expanded through. If a `C` or the `E` is left unmarked, the map is rejected.

The first version was recursive. A 600 x 600 open map (360,000 cells) overflowed the stack and crashed it. `tests/run_tests.sh` generates that map and expects a clean error instead.

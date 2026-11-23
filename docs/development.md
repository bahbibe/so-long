# Development

## Build

`make` builds `libft`, `gnl` and, on Linux, the bundled MiniLibX, then the `so_long` binary. Other targets: `make clean`, `make fclean`, `make re`, `make unit`.

MiniLibX also builds a small demo of its own that needs `libbsd`. The Makefile ignores that demo failing, because only `libmlx.a` is used.

On macOS the Makefile links the system MiniLibX (`-lmlx -framework OpenGL -framework AppKit`). I have not tested that path recently.

## Tests

`make unit` builds and runs two programs. Neither needs a window.

- `tests/test_ghosts.c`: ghost setup, shortest path chase, no stacking, walled off ghosts and the no-ghost case.
- `tests/test_render.c`: the pixel primitives, the sprites and the digit font. It checks clipping at every edge, NULL and bad buffers, and that nothing is written outside the frame (the buffers are surrounded by guard bytes). Run `DUMP=scene.ppm tests/test_render` to save a sample scene as a PPM image.

`tests/run_tests.sh` runs the real binary against the maps in `tests/maps` and checks the exit status and the error message for each case. Valid maps are started and killed after one second. `mlx_init` needs a display, so on a headless box run it under Xvfb:

```sh
make
xvfb-run tests/run_tests.sh
```

Set `BIN=/path/to/so_long` to test another binary. The script also generates a 600x600 open map to check that the reachability test does not overflow the stack.

## Ghost speed

Ghosts step every `GHOST_DELAY` milliseconds (`includes/so_long.h`, default 450) and glide to the next tile. The loop reads the clock with `gettimeofday` and sleeps with `usleep` between frames. These two functions are outside the usual 42 allowed list, so if you need to follow that list, `src/clock.c` and `tick()` in `src/ghost_anim.c` are the only places to change.

Change the delay at build time:

```sh
make re FLAGS="-Wall -Wextra -Werror -O2 -DGHOST_DELAY=300"
```

## Source layout

```
main.c               entry point and main loop setup
src/error_checkers.c file name check, check(), error reporting
src/map_checkers.c   shape, walls, tokens, token counts
src/path_checker.c   iterative flood fill and reachability check
src/helpers.c        map reading and copying, cleanup
src/init.c           game state and window setup
src/frame.c          off-screen frame buffers, graphics cleanup
src/draw_shapes.c    pixel, rectangle, circle, dimming primitives
src/draw_tiles.c     floor, wall, coin and door sprites
src/draw_actors.c    player and ghost sprites
src/draw_hud.c       digit font and the top bar
src/render.c         frame composition and presentation
src/scene.c          items, ghosts and the end panel
src/clock.c          millisecond clock and interpolation
src/animations.c     movement and key handling
src/ghosts.c         ghost setup, cleanup and lookup
src/ghost_move.c     breadth first search and ghost steps
src/ghost_anim.c     main loop tick (ghost timer, redraw when needed)
includes/libft       libft
includes/gnl         get_next_line
minilibx-linux/      MiniLibX for Linux (built by make on Linux)
maps/                sample map
tests/               test script, test maps and unit tests
docs/                these docs and the screenshots
```

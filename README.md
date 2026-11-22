# so_long

A small 2D game written in C with MiniLibX, built for the 42 school curriculum. You move a player around a map, collect every collectible, run from the ghosts that chase you and reach the exit.

## Requirements

- A C compiler (`cc`) and `make`.
- macOS with MiniLibX installed (`-lmlx -framework OpenGL -framework AppKit`), or
- Linux with the X11 development files (`libx11-dev`, `libxext-dev`). MiniLibX for Linux is bundled in `minilibx-linux/` (a copy of [42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux) at commit `7dc53a4`) and `make` builds it.

## Build

```sh
git clone https://github.com/bahbibe/so-long.git
cd so-long
make
```

`make` builds the bundled `libft` and `gnl` libraries (and MiniLibX on Linux), then the `so_long` binary. Other targets: `make clean`, `make fclean`, `make re`, `make unit` (see Tests).

## Run

The game has no asset files: every sprite is drawn in code, so it runs from any directory.

```sh
./so_long maps/map1.ber
```

## Controls

| Key | Action |
| --- | --- |
| `W` / `Up` | Move up |
| `S` / `Down` | Move down |
| `A` / `Left` | Move left |
| `D` / `Right` | Move right |
| `ESC` or `Q` | Quit |
| Window close button | Quit |

## Rules

- Collect every collectible (`C`). The door at the exit (`E`) opens once all of them are taken. Walking into it before that does nothing.
- Reach the opened exit to win.
- Ghosts (`G`) hunt you. They take one step toward you every `GHOST_DELAY` ms (see Ghost speed), along the shortest path around walls. Touching a ghost ends the game with a loss, whether you walk into it or it reaches you. Ghosts pass over collectibles and the exit, and two ghosts never share a tile. A ghost that is walled off from you stays where it is.
- Walls (`1`) block movement.
- The bar at the top of the window shows the number of collectibles left (coin icon) and the number of moves (arrow icon). Only moves that actually change the player's position are counted. Bumping into a wall or a closed door is not a move.
- After a win or a loss the game stops accepting moves. Press `ESC` or `Q` to exit.

## Map format

A map is a text file with the `.ber` extension (a name that is only `.ber` is rejected).

| Char | Meaning |
| --- | --- |
| `1` | Wall |
| `0` | Empty floor |
| `P` | Player start (exactly one) |
| `E` | Exit (exactly one) |
| `C` | Collectible (at least one) |
| `G` | Ghost start tile (optional, any number) |

Rules checked at start-up:

- The map is a rectangle. One final newline at the end of the file is allowed. Blank lines are not.
- The map is surrounded by walls.
- Only the characters above appear.
- There is one `P`, one `E` and at least one `C`.
- Every `C` can be reached from `P`, and `E` can be reached once the collectibles are taken. The check uses the ghosts' start tiles as walls, so a collectible that can only be reached through a ghost's start tile counts as unreachable.

Example (`maps/map1.ber` is a bigger one):

```
11111
1P0C1
1E0G1
11111
```

Each tile is 115 px (`SCALE` in `includes/so_long.h`), and the window has one extra row for the move counter. Large maps give a window larger than the screen, so keep maps small.

## Errors

On an invalid map or a start-up failure the program prints `Error:` and a message on stderr and exits with status 1.

| Message | Cause |
| --- | --- |
| `Usage: ./so_long <map_file.ber>` | Wrong number of arguments |
| `Invalid file name` | File name does not end in `.ber` |
| `Can not read from file` | File missing, unreadable, a directory, or empty |
| `Invalid Map` | Lines have different lengths, or a blank line at the end |
| `Map is not limited by walls` | A border cell is not `1` |
| `Invalid token` | A character other than `P E C 0 1 G` |
| `Duplicate or missing token` | Not exactly one `P` and one `E`, or no `C` |
| `Player Can't reach all collectibles` | A `C` is cut off from `P` |
| `Player Can not exit` | `E` is cut off from `P` |
| `Can not initialize MiniLibX` | `mlx_init` failed |
| `Can not create frame buffer` | `mlx_new_image` failed or the display is not 32 bits per pixel |
| `Can not create window` | `mlx_new_window` failed |
| `Out of memory` | An allocation failed |

## Ghost speed

Ghosts step every `GHOST_DELAY` milliseconds (`includes/so_long.h`, default 450) and glide to the next tile. The loop reads the clock with `gettimeofday` and sleeps with `usleep` between frames, so these two functions are used on top of the usual MiniLibX ones. Change the delay at build time:

```sh
make re FLAGS="-Wall -Wextra -Werror -O2 -DGHOST_DELAY=300"
```

## Tests

`tests/run_tests.sh` runs the binary against the maps in `tests/maps` and checks the exit status and the error message for each case. Valid maps are started and killed after one second. A display is needed because `mlx_init` runs before the window opens (`xvfb-run tests/run_tests.sh` works on a headless Linux box).

```sh
make
tests/run_tests.sh
```

Set `BIN=/path/to/so_long` to test another binary.

`make unit` builds and runs two programs, neither needs a window. `tests/test_ghosts.c` tests the ghost logic: setup, shortest path chase, no stacking, walled off ghosts and the no-ghost case. `tests/test_render.c` draws into plain buffers and checks the primitives, the sprites and the digit font: clipping at every edge, NULL and bad buffers, and that nothing is written outside the frame. Run `DUMP=scene.ppm tests/test_render` to save a sample scene as a PPM image.

## Project layout

```
main.c               entry point and main loop setup
src/error_checkers.c file name check, check(), error reporting
src/map_checkers.c   shape, walls, tokens, token counts
src/path_checker.c   flood fill and reachability check
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
tests/               test script, test maps and ghost unit tests
```

## License

MIT. See [LICENSE](LICENSE). This project was written as part of the 42 school curriculum. `minilibx-linux/` is third party code and keeps its own license (see `minilibx-linux/LICENSE`).

Created by Boubker Ahbibe.

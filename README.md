# so_long

A small 2D game written in C with MiniLibX, built for the 42 school curriculum. You move a player around a map, collect every collectible, avoid the ghosts and reach the exit.

## Requirements

- macOS with MiniLibX installed (`-lmlx -framework OpenGL -framework AppKit`). The Makefile and the key codes in `includes/so_long.h` are macOS only.
- A C compiler (`cc`) and `make`.

## Build

```sh
git clone https://github.com/bahbibe/so-long.git
cd so-long
make
```

`make` builds the bundled `libft` and `gnl` libraries, then the `so_long` binary. Other targets: `make clean`, `make fclean`, `make re`.

## Run

Run the game from the repository root. Textures are loaded from `./img`, so another working directory fails with `Can not load textures, run from repo root`.

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
- Touching a ghost (`G`) ends the game with a loss.
- Walls (`1`) block movement.
- The top row of the window shows `NUMBER OF MOVES : <n>`. Only moves that actually change the player's position are counted. Bumping into a wall or a closed door is not a move.
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
| `G` | Ghost (optional, any number) |

Rules checked at start-up:

- The map is a rectangle. One final newline at the end of the file is allowed. Blank lines are not.
- The map is surrounded by walls.
- Only the characters above appear.
- There is one `P`, one `E` and at least one `C`.
- Every `C` can be reached from `P`, and `E` can be reached once the collectibles are taken. Ghosts block the path, so a collectible that can only be reached through a ghost counts as unreachable.

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
| `Can not load textures, run from repo root` | An `.xpm` file in `./img` could not be loaded |
| `Can not create window` | `mlx_new_window` failed |
| `Out of memory` | An allocation failed |

## Tests

`tests/run_tests.sh` runs the binary against the maps in `tests/maps` and checks the exit status and the error message for each case. Valid maps are started and killed after one second. A display is needed because `mlx_init` runs before the window opens.

```sh
make
tests/run_tests.sh
```

Set `BIN=/path/to/so_long` to test another binary.

## Project layout

```
main.c               entry point and main loop setup
src/error_checkers.c file name check, check(), error reporting
src/map_checkers.c   shape, walls, tokens, token counts
src/path_checker.c   flood fill and reachability check
src/helpers.c        map reading and copying, cleanup
src/init.c           game state, texture loading, window setup
src/textures.c       rendering and the move counter
src/animations.c     movement, key handling, ghost animation
includes/libft       libft
includes/gnl         get_next_line
img/                 XPM textures
maps/                sample map
tests/               test script and test maps
```

## License

MIT. See [LICENSE](LICENSE). This project was written as part of the 42 school curriculum.

Created by Boubker Ahbibe.

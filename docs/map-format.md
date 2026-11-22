# Map format

A map is a text file with the `.ber` extension. A name that is only `.ber` is rejected.

| Char | Meaning |
| --- | --- |
| `1` | Wall |
| `0` | Empty floor |
| `P` | Player start (exactly one) |
| `E` | Exit (exactly one) |
| `C` | Collectible (at least one) |
| `G` | Ghost start tile (optional, any number) |

Example (`maps/map1.ber` is a bigger one):

```
11111
1P0C1
1E0G1
11111
```

## Checks at start-up

- The map is a rectangle. One final newline at the end of the file is allowed. Blank lines are not.
- The map is surrounded by walls.
- Only the characters above appear.
- There is one `P`, one `E` and at least one `C`.
- Every `C` can be reached from `P`, and `E` can be reached once the collectibles are taken. The check treats ghost start tiles as walls. A collectible that can only be reached through a ghost's start tile counts as unreachable.

Each tile is 48 px (`TILE` in `includes/so_long.h`) and the window has a 32 px bar on top. There is no scaling, so a very large map gives a window larger than the screen.

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

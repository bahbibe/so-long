#!/bin/sh
# Usage: [BIN=./so_long] tests/run_tests.sh   (from the repo root, after `make`)
# Checks map validation and CLI errors. Needs a display for mlx_init.

BIN=${BIN:-./so_long}
BIN=$(cd "$(dirname "$BIN")" && pwd)/$(basename "$BIN")
fails=0
dir=tests/maps
tmp=$(mktemp -d) || exit 1
trap 'rm -rf "$tmp"' EXIT

# expect_error <message> <args...>: exit code 1 and message on stderr
expect_error()
{
	msg=$1
	shift
	out=$("$BIN" "$@" 2>&1 >/dev/null)
	rc=$?
	if [ "$rc" -eq 1 ] && printf '%s' "$out" | grep -q "$msg"; then
		echo "ok   $*"
	else
		echo "FAIL $* (rc=$rc, got: $out)"
		fails=$((fails + 1))
	fi
}

# expect_valid <map>: no error. The game window stays open, so kill it.
expect_valid()
{
	"$BIN" "$1" >/dev/null 2>"$tmp/err" &
	pid=$!
	sleep 1
	if kill "$pid" 2>/dev/null; then
		echo "ok   $1"
		return
	fi
	wait "$pid"
	rc=$?
	if [ "$rc" -eq 0 ]; then
		echo "ok   $1"
	else
		echo "FAIL $1 (rc=$rc, got: $(cat "$tmp/err"))"
		fails=$((fails + 1))
	fi
}

expect_error "Usage"
expect_error "Usage" a.ber b.ber
expect_error "Invalid file name" ber
expect_error "Invalid file name" ""
expect_error "Invalid file name" .ber
expect_error "Invalid file name" "$dir/ok_nonl.txt"
expect_error "Can not read from file" "$dir/does_not_exist.ber"
mkdir "$tmp/dir.ber"
expect_error "Can not read from file" "$tmp/dir.ber"
expect_error "Can not read from file" "$dir/bad_empty.ber"
expect_error "Invalid Map" "$dir/bad_notrect.ber"
expect_error "Invalid Map" "$dir/bad_blank_end.ber"
expect_error "not limited by walls" "$dir/bad_open.ber"
expect_error "not limited by walls" "$dir/bad_east_open.ber"
expect_error "Invalid token" "$dir/bad_token.ber"
expect_error "Duplicate or missing token" "$dir/bad_noexit.ber"
expect_error "Duplicate or missing token" "$dir/bad_2player.ber"
expect_error "Duplicate or missing token" "$dir/bad_nocoll.ber"
expect_error "Duplicate or missing token" "$dir/bad_newline_only.ber"
expect_error "reach all collectibles" "$dir/bad_unreach_c.ber"
expect_error "reach all collectibles" "$dir/bad_ghost_blocks.ber"
expect_error "Can not exit" "$dir/bad_unreach_e.ber"
# big open map: the old recursive flood fill overflowed the stack here
awk 'BEGIN { n = 600
	for (i = 0; i < n; i++) {
		row = ""
		for (j = 0; j < n; j++) {
			c = "0"
			if (i == 0 || j == 0 || i == n - 1 || j == n - 1) c = "1"
			if (i == 1 && j == 1) c = "P"
			if (i == 1 && j == 2) c = "C"
			if (i == n - 2 && j == n - 2) c = "E"
			if ((i == n - 3 && j == n - 2) || (i == n - 2 && j == n - 3)) c = "1"
			row = row c
		}
		print row
	} }' > "$tmp/big.ber"
expect_error "Can not exit" "$tmp/big.ber"
expect_valid "$dir/ok_nonl.ber"
expect_valid "$dir/ok_trailing_nl.ber"
expect_valid maps/map1.ber
# no assets are loaded from disk: the game starts from any directory
cp "$dir/ok_nonl.ber" "$tmp/a.ber"
(cd "$tmp" && "$BIN" a.ber >/dev/null 2>"$tmp/err") &
pid=$!
sleep 1
if kill "$pid" 2>/dev/null; then
	echo "ok   run outside repo root"
else
	echo "FAIL run outside repo root (got: $(cat "$tmp/err"))"
	fails=$((fails + 1))
fi

[ "$fails" -eq 0 ] && echo "all tests passed" && exit 0
echo "$fails test(s) failed"
exit 1

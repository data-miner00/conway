# Conway

Conway's Game of Life in C attempt.

## Build & Run

1. Build all

```
make build
```

2. Run the CLI frontend

```
make run
```

3. Run the ncurses (TUI) frontend

```
make rn
```

4. Test

```
make test
```

5. Format

```
make format
```

## Nix

For Nix users, use `nix-shell` to activate the environment.

```
nix-shell
```

It is important to not mix the nix environment with the system environment. Verify by grepping the `CURSES_INCLUDE_PATH` variable.

```
grep CURSES_INCLUDE_PATH build/CMakeCache.txt
```

If it shows `/usr/include`, then the build is still referencing the system curses library. If it shows `/nix/store/...`, then the build is referencing the nix curses library.

To reset the build, remove it and rebuild.

```
rm -rf build && make build
```

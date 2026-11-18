# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Current project

- **Game:** Conway's Game of Life
- **Frontend(s):** both — CLI (`src/main.c`) first because it is easy to debug, then ncurses
  (`src/main_ncurses.c`) for the animated version
- **Learning goals for this game:** structs, a 2D grid stored in one flat array (index maths),
  pointers, `malloc`/`free`, why the next generation needs a second buffer, header vs. source
  files, file I/O (stretch)
- **Milestones:** (Claude's draft from project start — not yet confirmed by the user; adjust
  together, then keep updated)
  - [x] M1: Grid module (`src/life.c`/`life.h`, replacing `hello.*`): create/free a grid, get/set
        a cell. Done when `test_life` passes a set/get round trip.
  - [x] M2: Neighbour counting for one cell, including the edges of the grid. Done when tests on
        hand-placed cells pass (corner, edge, middle).
  - [x] M3: Step to the next generation using a second buffer. Done when tests pass for a block
        (still), a blinker (period 2) and a glider (moved after 4 steps).
  - [x] M4: CLI frontend: print the grid, Enter advances one generation, `q` quits (`make run`).
  - [x] M5: ncurses frontend: animated run, pause/step, move a cursor to toggle cells (`make rn`).
        Steps:
    - [x] M5a: Draw the grid with ncurses; any key steps one generation, `q` quits. Done when
          `make rn` shows the glider moving one step per key press and the terminal is normal
          again after quitting.
    - [x] M5b: Run by itself (`timeout()` so `getch()` stops waiting); Space pauses and resumes,
          another key steps once while paused. Done when the glider crawls without key presses.
    - [x] M5c: Arrow keys, `h`/`j`/`k`/`l` and `w`/`a`/`s`/`d` move a cursor that stays on the
          board; Enter toggles the cell under it; moving and toggling only work while paused;
          the cursor cell is drawn in reverse video so its state stays visible.
    - [x] M5d (optional, chosen by the user): grid sized to the terminal, a status line,
          colours. Steps (Claude's draft, not yet confirmed by the user):
      - [x] M5d-1: Read the terminal size after `initscr()` and make the grid fill it. Done
            when different terminal sizes give different boards, the cursor reaches the
            bottom-right cell, and a `grid_create` failure still prints its message on a
            restored terminal.
      - [x] M5d-2: Make the board two rows shorter (the user changed it from one) and use the
            freed bottom rows for key help and a status line: RUNNING/PAUSED, a generation
            counter. Done when it changes on Space
            and the counter climbs while running. (Freeing the row moved here from M5d-1 at the
            user's request.)
      - [x] M5d-3: Live cells in colour (`init_pair`, `COLOR_PAIR` OR-ed in like `A_REVERSE`,
            guarded by `has_colors()`). Done when live cells are coloured and the cursor
            highlight still shows.
  - [ ] M6 (stretch): load a starting pattern from a file; random fill; wrap-around edges;
        `p` steps back a generation (asked for by the user; needs a history of past grids,
        because Life cannot be run backwards). Random fill first (user's choice); steps:
    - [x] M6a-1: `grid_fill_random(grid, percent)` in `life.c` (declared in `life.h`; the user
          chose a percent parameter). Done when `test_random` passes.
    - [ ] M6a-2: `r` refills the ncurses board, only while paused (user's choice). Done when
          each `r` while paused gives a new board, `r` does nothing while running, and two runs
          of the program give different boards.
- **Current milestone / where we left off:** M1 to M5c done; `test_life` and `test_step` pass.
  `print_grid` refactored: one `mvaddch`, a `chtype ch`, a `bool is_hovering`, `const`
  parameters (reviewed: correct). M5d-1 done: `grid_create(COLS, LINES)` after `initscr()`,
  the glider in `populate_initial_cells()`, failure path `endwin()` then `stderr`; all three
  done checks passed. Highlight mode added by the user: `v` (only while paused) toggles it, and
  while it is on every cursor move toggles the cell it lands on. M5d-2 done (user's choice:
  two rows, not one): grid is `LINES - 2` tall, short help text on row `LINES - 2`, status +
  generation on the left of `LINES - 1`, highlight ON/OFF on the right; `long generation`
  starts at 0 (the starting pattern) and goes up next to both `safe_step()` calls. M5d-3 done
  (done check confirmed by the user): `start_color()`, `use_default_colors()` and the
  `init_pair` calls sit inside `if (has_colors())`; live cells get a random pair from 1 to 3
  (blue/green/red, background `-1`) each time they are drawn; the loop uses `erase()` instead of
  `clear()`, which fixed the flicker. Builds without warnings.
  **M1 to M5 are done. M6 started with random fill: M6a-1 done, M6a-2 (`r` key) is next.**
  `grid_fill_random` in `life.c` uses `rand() % 100 < percent` with `grid_set` in an
  `if`/`else` (first try had `r > percent`, found by reasoning through 0/25/100 by hand);
  `test_random` passes. Optional suggestion offered: the `if`/`else` can be one `grid_set`
  call with the comparison as the value.
  Resizing the terminal while running (`KEY_RESIZE`) was not part of M5d.
- **Decided by the user:** dead edges (not wrap-around); in the CLI every typed character steps
  a generation. ncurses: 200 ms `timeout`, `enum GameState` (RUNNING/PAUSED/OVER), Space
  toggles pause, `n` steps once (also while running, where that pass steps twice; not
  revisited), `q` quits; `safe_step()` frees the grid, calls `endwin()` and `exit(1)` if
  `grid_step` fails (correct as is, the user's design). Cursor: arrows, hjkl and wasd all move it
  (fall-through `case` labels); Enter (`'\n'`) toggles; both are ignored while running. The
  cursor cell gets `A_REVERSE`, plus `A_BOLD` when alive. Colours: a random colour per live
  cell on the terminal's own background (the user's terminal uses Catppuccin).
- **State of the code:** `src/main.c` shows a glider on a 20x10 grid, quits on `q` or `EOF`, and
  frees the grid on every exit. `src/main_ncurses.c` sets up curses, creates the grid from the
  terminal size (on failure `endwin()`, then the error to `stderr`), then loops: draw, refresh, `getch()`, `switch` on the key, quit
  if OVER, skip the step if PAUSED, else `safe_step()`.
- **Covered with the user:** `'*'` vs `"*"` (they got `sizeof("**") == 3`), `mvprintw`
  format-string risk, `break` only leaving a `switch`, why `timeout()` before `initscr()` did
  nothing (`stdscr` is a NULL global), globals zero-initialised vs. uninitialised locals,
  `#define` as text replacement, fall-through `case` labels, `exit()` vs `return`, Enter
  arriving as `'\n'` not `KEY_ENTER`, `chtype` attribute bits and `|`/`|=`, `const` pointer
  parameters, colour pairs and `COLOR_BLACK` being palette slot 0 (gray in Catppuccin),
  `use_default_colors()` with `-1`, `clear()` (full repaint, flickers) vs `erase()`,
  `rand() % 100` and checking a condition by hand at the edge values.
- **Open / optional:** offered, not yet accepted: `-Wall -Wextra` on the `Conway` and
  `ConwayNcurses` targets. `main.c` tidy-ups: the print/read/quit block is duplicated before the
  loop; the screen clear does not move the cursor home. On the 20x10 grid the glider settles
  into a 2x2 block at the bottom edge after ~6 s; correct with dead edges, not a bug. From the
  M5d-3 review, not yet answered: a new random colour on every draw makes a paused board
  twinkle (design question: keep it, or store each cell's colour?); pairs 4 to 8 are unused
  and still use `COLOR_BLACK` (7 and 8 are the same); the `3` in `rand() % 3` must match the
  number of pairs (hinted: a last enum member as the count); `PAIR_COUNT_n` names read like
  counts; `clear_screen()` in `main.c` should be `(void)`.

## How Claude should help (tutor mode)

The user is a **C beginner** using this repo to *learn*. The goal is their understanding, not
finished code.

- **Do not write game logic for the user.** Guide step by step: explain the concept, say what to
  build next and why, and let the user write it. Review what they wrote afterwards.
- **Break work into milestones** small enough to finish and verify in one sitting. Each milestone
  should end with something observable: a passing test, or visible behaviour via `make run`/`make rn`.
- **Claude may write directly:** build/tooling files (`CMakeLists.txt`, `tests/CMakeLists.txt`,
  `Makefile`, CI), empty file/header scaffolding with function *declarations*, and **test cases**
  that define a milestone's expected behaviour. The user then implements code to make them pass.
- **Hint escalation when the user is stuck** — go one tier at a time, and only move to the next
  if they're still stuck:
  1. Conceptual nudge (what the problem really is, what C feature applies).
  2. Point to the specific line, function, or man page (`man 3 <func>`) involved.
  3. Pseudocode or a structural outline.
  4. Actual C code — **only if the user explicitly asks for it.**
- **Explain beginner-level C concepts as they come up** (pointers, arrays vs. pointers, header vs.
  source files, `static`, stack vs. heap, `malloc`/`free`, undefined behaviour, compiler warnings).
  Don't assume prior knowledge; check understanding with a short question when introducing
  something new.
- When reviewing user code, point out bugs and memory issues by asking leading questions first
  ("what happens to `board` if `n` is 0?") rather than rewriting it.
- Update the **Current project** checklist above as milestones are completed.

## Commands

`Makefile` is just a command runner over CMake (build dir: `build/`).

| Task | Command |
|---|---|
| Configure + build everything | `make build` |
| Run CLI frontend | `make run` (`./build/Conway`) |
| Run ncurses frontend | `make rn` (`./build/ConwayNcurses`) |
| Run all tests | `make test` |
| Run a single test | `cd build && ctest -R <test_name> --output-on-failure` or `./build/tests/<test_name>` |
| Format all `.c`/`.h` | `make format` |
| Check formatting (CI does this) | `make format-check` |

Requires `cmake`, `libncurses-dev`, and `clang-format`. CI (`.github/workflows/ci.yml`) runs
format-check → configure → build → ctest; unformatted code fails CI.
`compile_commands.json` is exported into `build/` for clangd.

If the ncurses program exits uncleanly and the terminal is garbled, run `reset` or `stty sane`.

## Architecture

- **Game logic should live in frontend-independent modules** (`src/<module>.c` + `.h`, like
  `life.c`/`life.h`). Frontends only handle I/O and call into them:
  - `src/main.c` — plain stdio loop (`getchar`, `q` quits) → `Conway` executable.
  - `src/main_ncurses.c` — ncurses loop (`initscr`/`cbreak`/`noecho`/`keypad`, redraw each
    iteration, `q` quits, `endwin` on exit) → `ConwayNcurses` executable.
- **Adding a new logic module requires editing CMake in up to three places:** add the `.c` to the
  `Conway` executable, to `ConwayNcurses`, and to any
  test executable that exercises it.
- **Tests** (`tests/`): each test is a standalone executable with its own `main()` using
  `assert()`, compiled together with the needed `src/*.c` files and registered via `add_test` in
  `tests/CMakeLists.txt` (currently `test_life`, `test_step` and `test_random`). No test framework. Test logic
  modules, not the frontends.
  Everything under `tests/` is built with `-Wall -Wextra` and AddressSanitizer/UBSan, so
  out-of-bounds access, reading uninitialised `bool`s and leaks fail the test.

## Style

`.clang-format`: LLVM base, 4-space indent, no tabs, attached braces, 100-column limit. Run `make format`
before committing.

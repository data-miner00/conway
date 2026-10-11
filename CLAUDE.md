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
  - [ ] M2: Neighbour counting for one cell, including the edges of the grid. Done when tests on
        hand-placed cells pass (corner, edge, middle).
  - [ ] M3: Step to the next generation using a second buffer. Done when tests pass for a block
        (still), a blinker (period 2) and a glider (moved after 4 steps).
  - [ ] M4: CLI frontend: print the grid, Enter advances one generation, `q` quits (`make run`).
  - [ ] M5: ncurses frontend: animated run, pause/step, move a cursor to toggle cells (`make rn`).
  - [ ] M6 (stretch): load a starting pattern from a file; random fill; wrap-around edges.
- **Current milestone / where we left off:** M1 done, all five `test_life` tests pass. M2 is
  next; it is not scaffolded yet. `grid_get`/`grid_set` do no bounds checking, which M2 has to
  deal with: the user was asked what `grid_get(grid, 5, 0)` and `grid_get(grid, -1, 0)` return on
  a 5x3 grid and has not answered yet.

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
  `tests/CMakeLists.txt`. No test framework. Test logic modules, not the frontends.
  Everything under `tests/` is built with `-Wall -Wextra` and AddressSanitizer/UBSan, so
  out-of-bounds access, reading uninitialised `bool`s and leaks fail the test.

## Style

`.clang-format`: LLVM base, 4-space indent, no tabs, attached braces, 100-column limit. Run `make format`
before committing.

#include "life.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GETCH_TIMEOUT 200

enum GameState {
    GAME_STATE_RUNNING = 1,
    GAME_STATE_PAUSED = 2,
    GAME_STATE_OVER = 3,
};

typedef struct Point {
    int x;
    int y;
} point_t;

static void print_grid(const Grid *grid, const point_t *cursor) {
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            chtype ch;
            bool is_hovering = x == cursor->x && y == cursor->y;
            if (grid_get(grid, x, y)) {
                ch = '*';
                if (is_hovering) {
                    ch |= A_REVERSE | A_BOLD;
                }
            } else {
                ch = ' ';
                if (is_hovering) {
                    ch |= A_REVERSE;
                }
            }

            mvaddch(y, x, ch);
        }
    }
}

static void safe_step(Grid *grid) {
    bool ok = grid_step(grid);
    if (!ok) {
        grid_free(grid);
        endwin();
        exit(1);
    }
}

static void populate_initial_cells(Grid *grid) {
    grid_set(grid, 1, 0, true);
    grid_set(grid, 2, 1, true);
    grid_set(grid, 0, 2, true);
    grid_set(grid, 1, 2, true);
    grid_set(grid, 2, 2, true);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    point_t cursor = {0};

    initscr();              // enter curses mode, takes over the terminal
    timeout(GETCH_TIMEOUT); // max wait time for getch()
    cbreak();               // read input char-by-char, don't wait for Enter
    noecho();               // don't auto-print typed characters
    keypad(stdscr, TRUE);   // let getch() return arrow keys etc. as single KEY_* constants
    curs_set(1);            // primary cursor
    start_color();          // enable colors

    enum GameState state = GAME_STATE_RUNNING;
    bool isHighlightMode = false;
    long generation = 0;

    Grid *grid = grid_create(COLS, LINES - 2); // leave last 2 lines for status bar
    if (grid == NULL) {
        endwin();
        fprintf(stderr, "Failed to create grid\n");
        return 1;
    }

    populate_initial_cells(grid);

    while (true) {
        clear();
        mvprintw(LINES - 2, 0, "(Q)uit, (SPC) pause/resume, (N)ext, (V) highlight");
        mvprintw(LINES - 1, COLS - 20, "Highlight: %s", isHighlightMode ? "ON" : "OFF");
        mvprintw(LINES - 1, 0, "Status: %s, Generation: %ld",
                 state == GAME_STATE_PAUSED ? "PAUSED" : "RUNNING", generation);
        print_grid(grid, &cursor);
        refresh();
        int ch = getch();

        switch (ch) {
        case 'q':
            state = GAME_STATE_OVER;
            break;
        case ' ':
            if (state == GAME_STATE_RUNNING) {
                state = GAME_STATE_PAUSED;
            } else if (state == GAME_STATE_PAUSED) {
                state = GAME_STATE_RUNNING;
            }
            break;
        case 'n':
            generation++;
            safe_step(grid);
            break;
        case 'w':
        case 'k':
        case KEY_UP:
            if (state == GAME_STATE_PAUSED && cursor.y > 0) {
                cursor.y -= 1;

                if (isHighlightMode) {
                    grid_set(grid, cursor.x, cursor.y, !grid_get(grid, cursor.x, cursor.y));
                }
            }
            break;
        case 'a':
        case 'h':
        case KEY_LEFT:
            if (state == GAME_STATE_PAUSED && cursor.x > 0) {
                cursor.x -= 1;

                if (isHighlightMode) {
                    grid_set(grid, cursor.x, cursor.y, !grid_get(grid, cursor.x, cursor.y));
                }
            }
            break;
        case 's':
        case 'j':
        case KEY_DOWN:
            if (state == GAME_STATE_PAUSED && cursor.y < grid->height - 1) {
                cursor.y += 1;
                if (isHighlightMode) {
                    grid_set(grid, cursor.x, cursor.y, !grid_get(grid, cursor.x, cursor.y));
                }
            }
            break;
        case 'd':
        case 'l':
        case KEY_RIGHT:
            if (state == GAME_STATE_PAUSED && cursor.x < grid->width - 1) {
                cursor.x += 1;
                if (isHighlightMode) {
                    grid_set(grid, cursor.x, cursor.y, !grid_get(grid, cursor.x, cursor.y));
                }
            }
            break;
        case 'v':
            if (state == GAME_STATE_PAUSED) {
                isHighlightMode = !isHighlightMode;
            }
            break;
        // case KEY_ENTER: this does not work becoz it is the keypad's enter key
        case '\n':
            if (state == GAME_STATE_PAUSED) {
                grid_set(grid, cursor.x, cursor.y, !grid_get(grid, cursor.x, cursor.y));
            }
            break;
        default:
            break;
        }

        if (state == GAME_STATE_OVER) {
            break;
        }

        if (state == GAME_STATE_PAUSED) {
            continue;
        }

        generation++;
        safe_step(grid);
    }

    grid_free(grid);

    // if below is not run, can run `reset` or `stty sane` to reset terminal
    endwin();
    return 0;
}

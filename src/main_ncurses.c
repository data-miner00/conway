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

static void print_grid(Grid *grid, point_t *cursor) {
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            if (grid_get(grid, x, y)) {
                if (x == cursor->x && y == cursor->y) {
                    mvaddch(y, x, 'x');
                } else {
                    mvaddch(y, x, '*');
                }
            } else {
                if (x == cursor->x && y == cursor->y) {
                    mvaddch(y, x, 'x');
                } else {
                    mvaddch(y, x, ' ');
                }
            }
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

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Grid *grid = grid_create(20, 10);
    if (grid == NULL) {
        fprintf(stderr, "Failed to create grid\n");
        return 1;
    }

    point_t cursor = {0};

    grid_set(grid, 1, 0, true);
    grid_set(grid, 2, 1, true);
    grid_set(grid, 0, 2, true);
    grid_set(grid, 1, 2, true);
    grid_set(grid, 2, 2, true);

    initscr();              // enter curses mode, takes over the terminal
    timeout(GETCH_TIMEOUT); // max wait time for getch()
    cbreak();               // read input char-by-char, don't wait for Enter
    noecho();               // don't auto-print typed characters
    keypad(stdscr, TRUE);   // let getch() return arrow keys etc. as single KEY_* constants
    curs_set(1);            // primary cursor
    start_color();          // enable colors

    enum GameState state = GAME_STATE_RUNNING;

    while (true) {
        clear();
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
            safe_step(grid);
            break;
        case 'w':
        case 'k':
        case KEY_UP:
            if (state == GAME_STATE_PAUSED) {
                cursor.y -= 1;
            }
            break;
        case 'a':
        case 'h':
        case KEY_LEFT:
            if (state == GAME_STATE_PAUSED) {
                cursor.x -= 1;
            }
            break;
        case 's':
        case 'j':
        case KEY_DOWN:
            if (state == GAME_STATE_PAUSED) {
                cursor.y += 1;
            }
            break;
        case 'd':
        case 'l':
        case KEY_RIGHT:
            if (state == GAME_STATE_PAUSED) {
                cursor.x += 1;
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

        safe_step(grid);
    }

    grid_free(grid);

    // if below is not run, can run `reset` or `stty sane` to reset terminal
    endwin();
    return 0;
}

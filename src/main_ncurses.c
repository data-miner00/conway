#include "life.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void print_grid(Grid *grid) {
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            if (grid_get(grid, x, y)) {
                mvprintw(y, x, "*"); // mvaddch?
            } else {
                mvprintw(y, x, " ");
            }
        }
        move(y + 1, 0);
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Grid *grid = grid_create(20, 10);
    if (grid == NULL) {
        fprintf(stderr, "Failed to create grid\n");
        return 1;
    }

    grid_set(grid, 1, 0, true);
    grid_set(grid, 2, 1, true);
    grid_set(grid, 0, 2, true);
    grid_set(grid, 1, 2, true);
    grid_set(grid, 2, 2, true);

    initscr();            // enter curses mode, takes over the terminal
    cbreak();             // read input char-by-char, don't wait for Enter
    noecho();             // don't auto-print typed characters
    keypad(stdscr, TRUE); // let getch() return arrow keys etc. as single KEY_* constants
    curs_set(1);          // primary cursor
    start_color();        // enable colors

    bool is_running = true;

    while (true) {
        clear();
        print_grid(grid);
        refresh();
        int ch = getch();

        switch (ch) {
        case 'q':
            is_running = false;
            break;
        default:
            break;
        }

        if (!is_running) {
            break;
        }

        bool ok = grid_step(grid);
        if (!ok) {
            grid_free(grid);
            endwin();
            return 1;
        }
    }

    grid_free(grid);

    // if below is not run, can run `reset` or `stty sane` to reset terminal
    endwin();
    return 0;
}

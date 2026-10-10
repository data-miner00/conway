#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));

    initscr();            // enter curses mode, takes over the terminal
    cbreak();             // read input char-by-char, don't wait for Enter
    noecho();             // don't auto-print typed characters
    keypad(stdscr, TRUE); // let getch() return arrow keys etc. as single KEY_* constants
    curs_set(1);          // primary cursor
    start_color();        // enable colors

    bool is_running = true;

    while (is_running) {
        clear();

        mvprintw(0, 0, "Hello: %s", "world");

        refresh();
        int ch = getch();

        switch (ch) {
        case 'q':
            is_running = false;
            break;
        default:
            break;
        }
    }

    mvprintw(0, 0, "Bye: %s", "world");

    // if below is not run, can run `reset` or `stty sane` to reset terminal
    endwin();
    return 0;
}

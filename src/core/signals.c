#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <stddef.h>

volatile sig_atomic_t quit;

void handler(int s)
{
	quit = 1;
}
void setup_signal_handlers()
{
	signal(SIGINT, handler);
}
void cleanup_signal_handlers()
{
	signal(SIGINT, SIG_DFL);
}
void end_game()
{
	endwin();
	exit(0);
}

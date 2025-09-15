#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>

extern volatile sig_atomic_t quit;

void setup_signal_handlers();
void cleanup_signal_handlers();
void end_game();

#endif

#pragma once

#define HIGHLIGHT_COLOR "\x1B[1m\x1B[38;2;255;100;100m" 
#define HIGHLIGHT_COLOR_2 "\x1B[1m\x1B[38;2;100;255;100m" 
#define ERASESTYLE "\x1B[0m"

#ifdef NDEBUG
	const bool DEBUG_MODE = false;
#else
	const bool DEBUG_MODE = true;
#endif

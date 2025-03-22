#ifndef MPGB_PRINT_H
#define MPGB_PRINT_H

#include <cstdio>

#ifdef MPGB_ENABLE_PRINT
#define PRINTF(...) std::printf(__VA_ARGS__)
#define PUTS(...) std::puts(__VA_ARGS__)
#else
#define PRINTF(...)
#define PUTS(...)
#endif


#endif

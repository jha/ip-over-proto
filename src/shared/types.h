#ifndef _TYPES_H
#define _TYPES_H

#include <stdio.h>
#include <stdint.h>

typedef unsigned int bool_t;
#define FALSE   0
#define TRUE    1

#define STDIN   0
#define STDOUT  1
#define STDERR  2

typedef uint16_t port_t;
typedef uint32_t ipv4_t;

typedef int fd_t;

#define DBG(...) printf(__VA_ARGS__);
#define ERR(...) fprintf(stderr, __VA_ARGS__);

#define UNUSED(v) ((void) v)

#endif

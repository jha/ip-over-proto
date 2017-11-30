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

typedef uint8_t transport_t;

#define TRANSPORT_NONE  0
#define TRANSPORT_DNS   (1 << 0)
#define TRANSPORT_ICMP  (1 << 1)
#define TRANSPORT_UDP   (1 << 2)
#define TRANSPORT_TCP   (1 << 3)
#define TRANSPORT_ALL   (TRANSPORT_DNS | TRANSPORT_ICMP \
                        | TRANSPORT_UDP | TRANSPORT_TCP)

#define DBG(...) printf(__VA_ARGS__);
#define ERR(...) fprintf(stderr, __VA_ARGS__);

#define UNUSED(v) ((void) v)

#endif

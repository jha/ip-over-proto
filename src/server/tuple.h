#ifndef _TUPLE_H
#define _TUPLE_H

#include "types.h"

struct tuple {
    ipv4_t saddr, daddr;
    port_t sport, dport;
    uint8_t protocol;
};

typedef uint32_t tuple_hash_t;

tuple_hash_t
tuple_compute_hash(struct tuple *);

#endif

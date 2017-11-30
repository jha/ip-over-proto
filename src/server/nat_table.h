#ifndef _NAT_TABLE_H
#define _NAT_TABLE_H

#include <stdint.h>
#include "tuple.h"

#define NAT_TABLE_ELEMS (16 * 1024)

struct nat_table_entry {
    struct tuple tpl;
    fd_t fd;
};

struct nat_table_bucket {
    uint8_t length;
    struct nat_table_entry **entries;
};

/* We must translate everything ourselves, since we don't have IPTables. There
 * are two entries for every connection. The client entry deals with the
 * connection from the client tunnel, and the pub entry deals with the
 * connection to the public Internet */
struct nat_table {
    struct nat_table_bucket cli_buckets[NAT_TABLE_ELEMS];
    struct nat_table_bucket pub_buckets[NAT_TABLE_ELEMS];
};

struct nat_table *
nat_table_init(void);

bool_t
nat_table_add_entry(void);

void
nat_table_free(struct nat_table *);

#endif

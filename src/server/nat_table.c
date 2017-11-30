#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "nat_table.h"

struct nat_table *
nat_table_init(void)
{
    struct nat_table *ntbl;

    ntbl = calloc(1, sizeof (struct nat_table));
    if (ntbl == NULL) {
        ERR("nat::nat_table_init alloc failure: %s\n", strerror(errno));
        return NULL;
    }

    return ntbl;
}

bool_t
nat_table_add_entry(void)
{
    return TRUE;
}

void
nat_table_free(struct nat_table *ntbl)
{
    if (ntbl == NULL)
        return;
}

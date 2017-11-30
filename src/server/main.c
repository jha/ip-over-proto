#include <stdlib.h>
#include "types.h"
#include "nat_table.h"

int
main(int argc, char **args)
{
    struct nat_table *ntbl;

    UNUSED(argc);
    UNUSED(args);

    ntbl = nat_table_init();
    if (ntbl == NULL)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

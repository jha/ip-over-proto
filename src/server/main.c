#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include "types.h"
#include "nat_table.h"

static void
daemonize(void)
{
    fd_t null_fd;

    /* Our first fork to create a background process */
    switch (fork()) {
        case -1:
            ERR("main::daemonize : failed to fork: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        case 0: /* We are the child. Move along */
            break;
        default: /* This is the parent */
            exit(EXIT_SUCCESS);
    }

    /* Detach from terminal by creating an independent session */
    setsid();

    /* Fork a second time to set our parent process to init/1 */
    switch (fork()) {
        case -1:
            ERR("main::daemonize : failed to fork second time: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        case 0: /* We are the child's child. Move along */
            break;
        default: /* This is the first child */
            exit(EXIT_SUCCESS);
    }

    /* Create a write-only file descriptor to /dev/null */
    null_fd = open("/dev/null", O_RDONLY);
    if (null_fd == -1) {
        ERR("main::daemonize : cannot open /dev/null: %s\n", strerror(errno));
        return;
    }

    /* Rather than just closing STDIN, STDOUT, and STDERR we dup them to our
     * null_fd so that our printf and fprintfs don't potentially write to some
     * random network connection using 1, 2, or 3 as a fd */
    dup2(null_fd, STDIN);
    dup2(null_fd, STDOUT);
    dup2(null_fd, STDERR);
}

static void
parse_args(int argc, char *const *args,
    bool_t *no_daemonize, ipv4_t *bind, transport_t *transports)
{
    int i;

    *no_daemonize = FALSE;
    *bind = INADDR_ANY;
    *transports = TRANSPORT_ALL;

    for (i = 1; i < argc; i++) {
        int arglen;

        arglen = strlen(args[i]);
        if (arglen == 0) /* Cannot happen from a shell, but execve direct */
            DBG("main::parse_args : unknown argument ''\n");
        
        /* Check for options that have no value (begin with double dash) */
        if (strcmp(args[i], "--no-daemonize") == 0)
            *no_daemonize = TRUE;

        /* If this is the first argument, we can't run a comparison */
        if (i == 1)
            continue;

        /* Check the previous arg to see if the current arg
         * has any meaningful data */
        if (strcmp(args[i - 1], "-bind") == 0) {
            *bind = inet_addr(args[i]);
            if (*bind == INADDR_NONE) {
                *bind = INADDR_ANY;
                ERR("invalid bind address '%s'\n", args[i]);
            }
        } else if (strcmp(args[i - 1], "-transports") == 0) {
            char *cpy;
            char *pch;

            /* Make a copy of the current argument for modification */
            cpy = malloc(strlen(args[i]) + 1);
            strcpy(cpy, args[i]);

            *transports = TRANSPORT_NONE;
            for (pch = strtok(cpy, ",");
                pch != NULL; pch = strtok(NULL, ",")) {
                if (strcmp(pch, "dns") == 0)
                    *transports |= TRANSPORT_DNS;
                else if (strcmp(pch, "icmp") == 0)
                    *transports |= TRANSPORT_ICMP;
                else if (strcmp(pch, "udp") == 0)
                    *transports |= TRANSPORT_UDP;
                else if (strcmp(pch, "tcp") == 0)
                    *transports |= TRANSPORT_TCP;
                else {
                    ERR("main::parse_args : "
                        "unknown transport '%s'\n", pch);
                }
            }

            free(cpy);
        } else
            DBG("main::parse_args : unknown argument '%s'\n", args[i]);
    }
}

int
main(int argc, char **args)
{
    bool_t no_daemonize;
    ipv4_t bind;
    transport_t transports;
    struct nat_table *ntbl;

    /* Parse and check we have a valid config */
    parse_args(argc, args, &no_daemonize, &bind, &transports);
    if (transports == TRANSPORT_NONE)
        DBG("main::main : no transport with 0 options specified\n");
    if (bind == INADDR_LOOPBACK)
        DBG("main::main : server is binding to localhost... weird\n");

    if (no_daemonize == FALSE)
        daemonize();

    ntbl = nat_table_init();
    if (ntbl == NULL)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

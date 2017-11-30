#ifndef _CONFIG_H
#define _CONFIG_H

/* This file controls the different kinds of tunneling methods that are
 * enabled. If multiple tunneling methods are enabled, the client and
 * server will attempt to pick the fastest one based on availability. The
 * order of preference, from least preferred to most preferred, is
 * DNS, ICMP, TCP, UDP */

/* Enables IP over DNS. This is the slowest protocol
 * so it has the lowest priority out of any */
#define CONFIG_ENABLE_DNS

/* Enables IP over ICMP. This is close to native speed
 * but has the overhead of ICMP packets */
#define CONFIG_ENABLE_ICMP

/* Enables IP over TCP. A little worse than UDP but
 * still better than the other options */
#define CONFIG_ENABLE_TCP

/* Enables IP over UDP. This is the most optimal
 * protocol, which we prefer to use if possible */
#define CONFIG_ENABLE_UDP

/* Change undef to define to enable hardware-accelerated CRC hashing on
 * the server. You also need to add -msse4.2 to LFLAGS in the Makefile */
#undef CONFIG_ENABLE_HWCRC

#endif

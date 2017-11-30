#ifndef _DNS_H
#define _DNS_H


#include <stdint.h>

struct dns_header {
    uint16_t id;
    uint16_t options;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} __attribute__((packed));

struct dns_question {
    uint16_t qtype;
    uint16_t qclass;
} __attribute__((packed));

struct dns_resource {
    uint16_t type;
    uint16_t class;
    uint16_t ttl;
    uint16_t data_len;
} __attribute__((packed));

#endif

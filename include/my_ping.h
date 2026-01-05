/**
 * Created at: 03/08/2025 14:10 pm BST
 */

#ifndef MYPING_H
#define MYPING_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t id;
    uint16_t sequence;
} icmp_hdr_t;
#pragma pack(pop)

int my_ping(const char *ip_address);

#endif
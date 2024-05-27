#ifndef  PACKET_H
#define  PACKET_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define PACKET_SIZE 32
#define SH_SIZE 11
#define PAYLOAD_SIZE 17
#define ECC_SIZE 4

typedef struct {
    uint32_t target;
    uint32_t size;
    uint32_t service_header[SH_SIZE];
    uint32_t payload[PAYLOAD_SIZE];
    uint32_t ecc [ECC_SIZE];
} Packet;

#endif  /*PACKET_H*/

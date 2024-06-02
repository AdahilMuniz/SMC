#ifndef  PACKET_H
#define  PACKET_H

#include <stdio.h>
#include <stdint.h>
#include "ecc.h"

//@NOTE: All sizes are defined in number of flits
#define PACKET_SIZE 32
#define SH_SIZE 11
#define PAYLOAD_SIZE 17
#define ECC_SIZE 4

#define MSB (SH_SIZE + PAYLOAD_SIZE)*32 - 1
#define LSB 0

typedef struct {
    uint32_t target;
    uint32_t size;
    union{
        struct {
            uint32_t service_header[SH_SIZE];
            uint32_t payload[PAYLOAD_SIZE];
        };
        uint32_t pkt_payload[SH_SIZE+PAYLOAD_SIZE];
    };
    uint8_t ecc [ECC_SIZE*4];
} packet_t;

typedef struct {
    packet_t packet_error;
    int num_errors;
    int error_loc[32];  // Armazena até 32 locais de erro, pode ser ajustado conforme necessário
} multi_return;

// void sendpacket_t(packet_t packet);
// void receivepacket_t(packet_t packet);
// packet_t injectError(packet_t packet, uint16_t nb_errors);

void build_packet(uint32_t * payload, packet_t * packet, uint32_t target);
void print_packet( packet_t packet);
#endif  /*PACKET_H*/

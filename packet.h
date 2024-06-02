#ifndef  PACKET_H
#define  PACKET_H

#include <stdio.h>
#include <stdint.h>
#include "ecc.h"

//@NOTE: All sizes are defined in number of flits
#define SH_SIZE 11
#define PAYLOAD_SIZE 17
#define ECC_SIZE 4
#define PACKET_SIZE (SH_SIZE + PAYLOAD_SIZE + ECC_SIZE + 2)

#define MSB (SH_SIZE + PAYLOAD_SIZE)*32 - 1
#define LSB 0

#define CHANNEL_0 "chn0"
#define CHANNEL_1 "chn1"
#define CHANNEL_2 "chn2"

typedef struct {
    uint8_t * channel_name;
    FILE * fptr;
} connection_t;

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

void encode_packet(uint32_t * payload, packet_t * packet, uint32_t payload_size, uint32_t target, uint32_t pckt_seq_nb);
void print_packet(packet_t packet, uint32_t payload_size);

void connect(connection_t * connection, uint8_t * channel_name, uint8_t * con_type);
void close_connect(connection_t * connection);

void send_pckt(packet_t packet, connection_t * connection);
void recv_pckt(packet_t * packet, connection_t * connection);
uint8_t rcv_ack();
#endif  /*PACKET_H*/

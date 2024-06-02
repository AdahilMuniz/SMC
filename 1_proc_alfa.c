#include <stdlib.h>
#include "packet.h"

int main (){
    uint32_t payload [PAYLOAD_SIZE];
    packet_t packet;

    for (int i = 0; i < PAYLOAD_SIZE; i++) {
        payload[i] = rand();
    }
    
    encode_packet(payload, &packet, PAYLOAD_SIZE, 2024, 1);
    print_packet(packet, PACKET_SIZE);
    return 0;
}
#include <stdlib.h>
#include "packet.h"

int main (){
    uint32_t payload [PAYLOAD_SIZE];
    packet_t packet;

    for (int i = 0; i < PAYLOAD_SIZE; i++) {
        payload[i] = rand();
    }
    
    build_packet(payload, &packet, 2024, 1);
    print_packet(packet);
    return 0;
}
#include "packet.h"

void receivePacket(Packet packet) {
    // Simulação do envio do pacote pelo canal de comunicação
    printf("Pacote recebido: Target: %u Size: %u Service Header: ", packet.target, packet.size);
    for (int i = 0; i < SH_SIZE; i++) {
        printf("%u ", packet.service_header[i]);
    }
    printf("Payload: ");
    for (int i = 0; i < PAYLOAD_SIZE; i++) {
        printf("%u ", packet.payload[i]);
    }
    printf("ECC: ");
    for (int i = 0; i < ECC_SIZE; i++) {
        printf("%u ", packet.ecc[i]);
    }
}

Packet beta(Packet packet_rec) {
     
    // Recebe o pacote
    receivePacket(packet_rec);
    return packet_rec;
}

#include "packet.h"

void sendPacket(Packet packet) {
    // Simulação do envio do pacote pelo canal de comunicação
    printf("Pacote enviado: Target: %u Size: %u Service Header: ", packet.target, packet.size);
    for (int i = 0; i < 11; i++) {
        printf("%u ", packet.service_header[i]);
    }
    printf("Payload: ");
    for (int i = 0; i < PAYLOAD_SIZE; i++) {
        printf("%u ", packet.payload[i]);
    }
    printf("ECC: ");
    for (int i = 0; i < 4; i++) {
        printf("%u ", packet.ecc[i]);
    }
}


void receivePacket(Packet packet) {
    // Simulação do envio do pacote pelo canal de comunicação
    printf("Pacote enviado: Target: %u Size: %u Service Header: ", packet.target, packet.size);
    for (int i = 0; i < 11; i++) {
        printf("%u ", packet.service_header[i]);
    }
    printf("Payload: ");
    for (int i = 0; i < PAYLOAD_SIZE; i++) {
        printf("%u ", packet.payload[i]);
    }
    printf("ECC: ");
    for (int i = 0; i < 4; i++) {
        printf("%u ", packet.ecc[i]);
    }
}


Packet injectError(Packet packet, uint16_t nb_errors) {
    Packet result_packet;
    uint16_t position = 0;

    result_packet = packet;

    for (uint8_t i = 0; i < nb_errors; i++){
        position = rand() % (MSB + 1 - LSB) + LSB;
    }
    
    return result_packet;
}

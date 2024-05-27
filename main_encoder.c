// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <time.h>

// #define PACKET_SIZE 32
// #define SH_SIZE 11
// #define PAYLOAD_SIZE 17
// #define ECC_SIZE 4

// typedef struct {
//     uint32_t target;
//     uint32_t size;
//     uint32_t service_header[SH_SIZE];
//     uint32_t payload[PAYLOAD_SIZE];
//     uint32_t ecc [ECC_SIZE];
// } Packet;

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

int main() {
    Packet packet;
    srand(1); // Inicializar o gerador de números aleatórios (sempre igual)

    // Preencher os campos do pacote
    packet.target = 2024; // Exemplo de identificador para Beta
    packet.size = SH_SIZE + PAYLOAD_SIZE + ECC_SIZE; // Tamanho dos campos SH + payload
    // Preencher Service Header
    for (int i = 0; i < (SH_SIZE-2); i++) {
        packet.service_header[i] = i; // Valores de exemplo
    }
    packet.service_header[9] = 1; // Número de sequência do pacote
    packet.service_header[10] = PAYLOAD_SIZE; // Tamanho do payload
    // Preencher Payload
    for (int i = 0; i < PAYLOAD_SIZE; i++) {
        packet.payload[i] = rand();
    }
    // Preencher ECC
    for (int i = 0; i < ECC_SIZE; i++) {
        packet.ecc[i] = i; // Valores de exemplo
    }
    
    // Enviar o pacote
    sendPacket(packet);
    return 0;
}
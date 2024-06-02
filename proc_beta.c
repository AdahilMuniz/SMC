#include "packet.h"

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

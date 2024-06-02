#include <stdlib.h>
#include <stdio.h>
#include "packet.h"

// packet_t injectError(packet_t packet, uint16_t nb_errors) {
//     packet_t result_packet;
//     uint16_t position = 0;

//     result_packet = packet;

//     for (uint8_t i = 0; i < nb_errors; i++){
//         position = rand() % (MSB + 1 - LSB) + LSB;
//     }
    
//     return result_packet;
// }

// typedef struct {
//     packet_t packet_error;
//     int num_errors;
//     int error_loc;
// } multi_return;

// packet_t inject_error(packet_t packet_error) {
//     int field = rand() % 3;  // Escolhe aleatoriamente entre Service Header, Payload e ECC
//     switch (field) {
//         case 0: {  // Erro no Service Header
//             int index = rand() % SH_SIZE;
//             packet_error.service_header[index] = rand();
//             break;
//         }
//         case 1: {  // Erro no Payload
//             int index = rand() % PAYLOAD_SIZE;
//             packet_error.payload[index] = rand();
//             break;
//         }
//         case 2: {  // Erro no ECC
//             int index = rand() % ECC_SIZE;
//             packet_error.ecc[index] = rand();
//             break;
//         }
//     }
//     return packet_error;
// }

multi_return injectErrors(packet_t packet, uint16_t nb_errors) {
    multi_return result;
    result.packet_error = packet;
    result.num_errors = nb_errors;

    for (uint16_t i = 0; i < nb_errors; i++) {
        int field = rand() % 3;  // Escolhe aleatoriamente entre Service Header, Payload e ECC
        int index;
        switch (field) {
            case 0: {  // Erro no Service Header
                index = rand() % SH_SIZE;
                result.packet_error.service_header[index] = rand();
                result.error_loc[i] = index;  // Armazena a localização do erro
                break;
            }
            case 1: {  // Erro no Payload
                index = rand() % PAYLOAD_SIZE;
                result.packet_error.payload[index] = rand();
                result.error_loc[i] = SH_SIZE + index;  // Armazena a localização do erro
                break;
            }
            case 2: {  // Erro no ECC
                index = rand() % ECC_SIZE;
                result.packet_error.ecc[index] = rand();
                result.error_loc[i] = SH_SIZE + PAYLOAD_SIZE + index;  // Armazena a localização do erro
                break;
            }
        }
    }
    return result;
}


int main (){
    uint32_t payload [PAYLOAD_SIZE];
    packet_t packet;
    connection_t con;

    printf("[ERROR_INJECTOR] Starting Process Error Injector ...\n");
    printf("[ERROR_INJECTOR] Waiting connection ...\n");
    connect(&con, CHANNEL_0, "rb+");//Channel 0 is the communication channel between Error Injector and Alfa
    while(1) {
        printf("[ERROR_INJECTOR] Waiting for packet ...\n");
        recv_pckt(&packet, &con);
        print_packet(packet, PAYLOAD_SIZE);
    }

    close_connect(&con);
    printf("[ERROR_INJECTOR] Finishing Process Error Injector ...\n");
    return 0;
}
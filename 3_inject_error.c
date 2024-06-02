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


#define RAND_NONE  0b00000000
#define RAND_FIELD 0b00000001
#define RAND_FLIT  0b00000010
#define RAND_POS   0b00000100

typedef enum {
    SH_FIELD,
    PAYLOAD_FIELD,
    ECC_FIELD,
} field_t;

typedef struct {
    uint8_t error_rand;
    field_t field;
    uint8_t flit;
    uint32_t position;
    uint8_t nb_error;
} error_config_t;



void configure_error(packet_t * packet_mask,  error_config_t error_cfg) {
            
    field_t field;
    uint8_t flit;
    uint32_t position = 0;

    uint8_t pos_aux;

    if (error_cfg.error_rand != 0){
        if (error_cfg.error_rand & RAND_FIELD){
            field = rand() % 3;
        } else {
            field = error_cfg.field;
        }

        if (error_cfg.error_rand & RAND_FLIT){
            if (field == SH_FIELD){
                flit = rand() % SH_SIZE;
            } else if (field == PAYLOAD_FIELD){
                flit = rand() % PAYLOAD_SIZE;
            } else{
                flit = rand() % ECC_SIZE;
            }
        } else {
            if (field == SH_FIELD && error_cfg.flit > SH_SIZE){
                flit =SH_SIZE;
            } else if (field == PAYLOAD_FIELD && error_cfg.flit > PAYLOAD_SIZE){
                flit = PAYLOAD_SIZE;
            } else if (field == ECC_FIELD && error_cfg.flit > ECC_SIZE){
                flit = ECC_SIZE;
            } else{
                flit = error_cfg.flit;
            }
        }

        if (error_cfg.error_rand & RAND_POS){
            for (int i = 0; i < error_cfg.nb_error; i++){
                pos_aux = rand() % 32;
                position |= 0x00000001 << pos_aux;
            }
        } else {
            position = error_cfg.position;
        }
    } else {
        field = error_cfg.field;
        if (field == SH_FIELD && error_cfg.flit > SH_SIZE){
            flit =SH_SIZE;
        } else if (field == PAYLOAD_FIELD && error_cfg.flit > PAYLOAD_SIZE){
            flit = PAYLOAD_SIZE;
        } else if (field == ECC_FIELD && error_cfg.flit > ECC_SIZE){
            flit = ECC_SIZE;
        } else{
            flit = error_cfg.flit;
        }
        position = error_cfg.position;
    }

    switch (field) {
        case SH_FIELD: packet_mask->service_header[flit] |= position;
        case PAYLOAD_FIELD: packet_mask->payload[flit] |= position;
        case ECC_FIELD: packet_mask->ecc[flit] |= position;
    }
}

void inject_error(packet_t * packet, packet_t * packet_mask){
    //Apply to the packet
    // SH
    for (size_t i = 0; i < SH_SIZE; i++){
        packet->service_header[i] ^= packet_mask->service_header[i];
    }
    // PAYLOAD
    for (size_t i = 0; i < PAYLOAD_SIZE; i++){
        packet->payload[i] ^= packet_mask->payload[i];
    }
    // ECC
    for (size_t i = 0; i < ECC_SIZE; i++){
        packet->ecc[i] ^= packet_mask->ecc[i];
    }
}

void reset_mask(packet_t * packet_mask){
    // SH
    for (size_t i = 0; i < SH_SIZE; i++){
        packet_mask->service_header[i] = 0;
    }
    // PAYLOAD
    for (size_t i = 0; i < PAYLOAD_SIZE; i++){
        packet_mask->payload[i] = 0;
    }
    // ECC
    for (size_t i = 0; i < ECC_SIZE; i++){
        packet_mask->ecc[i] = 0;
    }
}

void reset_cfg(error_config_t * error_cfg){
    error_cfg->error_rand = 0;
    error_cfg->field      = 0;
    error_cfg->flit       = 0;
    error_cfg->position   = 0;
    error_cfg->nb_error   = 0;
}


int main (){
    uint32_t payload [PAYLOAD_SIZE];
    packet_t packet;
    packet_t packet_mask;
    error_config_t error_cfg;
    connection_t con_alfa;
    connection_t con_beta;

    printf("[ERROR_INJECTOR] Starting Process Error Injector ...\n");
    reset_mask(&packet_mask); //Reset mask
    reset_cfg(&error_cfg); //Reset configuration
    printf("[ERROR_INJECTOR] Waiting connection with Beta...\n");
    connect(&con_beta, CHANNEL_1, "ab+");//Channel 1 is the communication channel between Error Injector and Beta
    printf("[ERROR_INJECTOR] Waiting connection with Alfa...\n");
    connect(&con_alfa, CHANNEL_0, "rb+");//Channel 0 is the communication channel between Error Injector and Alfa
    while(1) {
        error_cfg.error_rand = RAND_NONE;
        error_cfg.field = PAYLOAD_FIELD;
        error_cfg.flit = 1;
        error_cfg.position = 0x00000001 << 1;
        error_cfg.nb_error = 1;
        configure_error(&packet_mask, error_cfg);
        printf("[ERROR_INJECTOR] Waiting for packet ...\n");
        recv_pckt(&packet, &con_alfa);
        //[call the injection error method here]
        inject_error(&packet, &packet_mask);
        print_packet(packet, PAYLOAD_SIZE);
        send_pckt(packet, &con_beta); //@NOTE: Just bypassa the packet with errors
    }

    close_connect(&con_beta);
    close_connect(&con_alfa);
    printf("[ERROR_INJECTOR] Finishing Process Error Injector ...\n");
    return 0;
}
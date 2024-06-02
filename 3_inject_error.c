#include <stdlib.h>
#include <stdio.h>
#include "packet.h"
#include "error_gen.h"


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
        scenario1(&packet_mask);
        printf("[ERROR_INJECTOR] Waiting for packet ...\n");
        recv_pckt(&packet, &con_alfa);
        //[call the injection error method here]
        inject_error(&packet, &packet_mask);
        print_packet(packet, PAYLOAD_SIZE);
        send_pckt(packet, &con_beta); //@NOTE: Just bypassa the packet with errors
        reset_mask(&packet_mask);
    }

    close_connect(&con_beta);
    close_connect(&con_alfa);
    printf("[ERROR_INJECTOR] Finishing Process Error Injector ...\n");
    return 0;
}
#include "packet.h"

int main(){
    uint32_t payload [PAYLOAD_SIZE];
    packet_t packet;
    pkt_error_t packet_err;
    uint32_t pkt_nb = 0;
    connection_t con_inject;
    connection_t con_alfa;
    FILE * output_fptr;

    printf("[PROC_BETA] Starting Process Beta ...\n");
    printf("[PROC_BETA] Waiting connection with Alfa...\n");
    connect(&con_alfa, CHANNEL_2, "ab+");//Channel 2 is the communication channel for acknowledgement between Beta and Alfa
    printf("[PROC_BETA] Waiting connection with Error Injector...\n");
    connect(&con_inject, CHANNEL_1, "rb+");//Channel 1 is the communication channel between Beta and Error Injector
    while(1) {
        output_fptr = fopen("output_file", "a+"); //Open output file
        printf("[PROC_BETA] Waiting for packet ...\n");
        recv_pckt(&packet, &con_inject);
        printf("[PROC_BETA] Packet before correction:\n");
        print_packet(packet, PAYLOAD_SIZE);
        packet_err = decode_packet(&packet, PAYLOAD_SIZE, 2024, pkt_nb);
        printf("[PROC_BETA] Packet after correction:\n");
        print_packet(packet, PAYLOAD_SIZE);
        if (packet_err == ECC_DE || packet_err == WRONG_SEQ_NB){
            send_ackno_reply(NACK, &con_alfa);
            pkt_nb = pkt_nb;
        } else if (packet_err == ECC_SE){
            send_ackno_reply(ACK_ERR, &con_alfa);
            fputs((char *) packet.payload, output_fptr); // Store the received packet
            pkt_nb ++;
        } else if (packet_err == NONE){
            send_ackno_reply(ACK, &con_alfa);
            fputs((char *) packet.payload, output_fptr); // Store the received packet
            pkt_nb ++;
        } else {
            //Do nothing (Different Target)
            pkt_nb ++;
        }
        fclose(output_fptr); //@NOTE: For some reason, we need to open and close the file for each written packet
    }

    close_connect(&con_alfa);
    close_connect(&con_inject);
    printf("[PROC_BETA] Finishing Process Beta ...\n");
    return 0;
    return 0;
}
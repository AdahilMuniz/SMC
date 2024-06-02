#include <stdlib.h>
#include <stdio.h>
#include "packet.h"

int main (){
    uint32_t payload [PAYLOAD_SIZE];
    uint32_t pkt_nb = 0;
    packet_t packet;
    ackno_packet_t reply;
    connection_t con_inject;
    connection_t con_beta;
    uint8_t file_content[PAYLOAD_SIZE*4];
    FILE * input_fptr;
    FILE * log_fptr;

    //Statistics
    uint32_t nb_ack     = 0;
    uint32_t nb_ack_err = 0;
    uint32_t nb_nack    = 0;

    input_fptr = fopen("input_file", "r");

    if(input_fptr == NULL) { //Check if file exists
      printf("[PROC_ALFA] Not able to open the file.");
      return -1;
    }

    printf("[PROC_ALFA] Starting Process Alfa ...\n");
    printf("[PROC_ALFA] Waiting connection with Error Injector...\n");
    connect(&con_inject, CHANNEL_0, "ab+"); //Channel 0 is the communication channel between Alfa and Error Injector
    printf("[PROC_ALFA] Waiting connection with Beta...\n");
    connect(&con_beta, CHANNEL_2, "rb+"); //Channel 2 is the communication channel between Alfa and Beta
    //@NOTE: I developed a version where the process run forever and wait to get something from file.
    //However, it needs to have a control to close and reopen the file several time, as this is not the 
    //goal of the project, I gave up on this and did this version that runs until end of file.
    while(fgets(file_content, PAYLOAD_SIZE*4, input_fptr)) {
        printf("[PROC_ALFA] Waiting for reading file ...\n");
        encode_packet((uint32_t * ) file_content, &packet, PAYLOAD_SIZE, 2024, pkt_nb);
        print_packet(packet, PAYLOAD_SIZE);
        send_pckt(packet, &con_inject);
        printf("[PROC_ALFA] Waiting for acknowledgement ...\n");
        recv_ackno_reply(&reply, &con_beta);
        while (reply == NACK){
          nb_nack++;
          pkt_nb = pkt_nb;
          send_pckt(packet, &con_inject);
          recv_ackno_reply(&reply, &con_beta);
        }
        if (reply == ACK_ERR){
          nb_ack_err++;
          pkt_nb ++;
        } else {
          nb_ack++;
          pkt_nb ++;
        }
    }
    printf("Statisticas:\n");
    printf("N# ACK      : %d\n", nb_ack);
    printf("N# ACK ERROR: %d\n", nb_ack_err);
    printf("N# NACK     : %d\n", nb_nack);
    printf("\n");
    close_connect(&con_inject);
    close_connect(&con_beta);
    fclose(input_fptr);

    //Writing Statistics
    log_fptr = fopen("alfa_log_file", "w+");
    fprintf(log_fptr, "Statisticas:\n");
    fprintf(log_fptr,"N# ACK      : %d\n", nb_ack);
    fprintf(log_fptr,"N# ACK ERROR: %d\n", nb_ack_err);
    fprintf(log_fptr,"N# NACK     : %d\n", nb_nack);
    fclose(log_fptr);

    printf("[PROC_ALFA] Finishing Process Alfa ...\n");
    return 0;
}
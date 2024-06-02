#include <stdlib.h>
#include <stdio.h>
#include "packet.h"

int main (){
    uint32_t payload [PAYLOAD_SIZE];
    uint32_t pkt_nb = 0;
    packet_t packet;
    connection_t con;
    uint8_t file_content[PAYLOAD_SIZE*4];
    FILE * fptr;

    fptr = fopen("input_file", "r");

    if(fptr == NULL) { //Check if file exists
      printf("[PROC ALFA] Not able to open the file.");
      return -1;
    }

    printf("[PROC ALFA] Starting Process Alfa ...\n");
    while(1) {
        //@NOTE: The file is not written until it is closed, so, we need to open and close connection inside this loop
        connect(&con, CHANNEL_0, "ab+"); //Channel 0 is the communication channel between Alfa an Error Injector
        printf("[PROC ALFA] Waiting for reading file ...\n");
        while(!fgets(file_content, PAYLOAD_SIZE*4, fptr));
        encode_packet((uint32_t * ) file_content, &packet, PAYLOAD_SIZE, 2024, pkt_nb);
        print_packet(packet, PAYLOAD_SIZE);
        send_pckt(packet, &con);
        pkt_nb ++;
        close_connect(&con);
    }
    printf("\n");

    fclose(fptr);

    printf("[PROC ALFA] Finishing Process Alfa ...\n");
    return 0;
}
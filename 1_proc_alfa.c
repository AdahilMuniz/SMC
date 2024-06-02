#include <stdlib.h>
#include <stdio.h>
#include "packet.h"

int main (){
    uint32_t payload [PAYLOAD_SIZE];
    uint32_t pkt_nb = 0;
    packet_t packet;
    uint8_t file_content[PAYLOAD_SIZE*4];
    FILE * fptr;

    fptr = fopen("input_file", "r");

    if(fptr == NULL) { //Check if file exists
      printf("Not able to open the file.");
      return -1;
    }

    while(fgets(file_content, PAYLOAD_SIZE*4, fptr)) {
        encode_packet((uint32_t * ) file_content, &packet, PAYLOAD_SIZE, 2024, pkt_nb);
        print_packet(packet, PAYLOAD_SIZE);
        pkt_nb ++;
    }
    printf("\n");

    return 0;
}
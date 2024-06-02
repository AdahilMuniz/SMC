#include "packet.h"

//@NOTE: The buildd_packet method consider constant PAYLOAD and ECC size

/**
 * \brief Set the packet parameters and caculate the ECCs for the each block
 *
 * 
 * \param payload Data Input.
 * \param packet Packet struct output.
 * \param payload_size Packet payload size.
 * \param target Header Target.
 * \param pckt_seq_nb Header Packet Sequence Number.
 * \return Void
 */

void encode_packet(uint32_t * payload, packet_t * packet, uint32_t payload_size, uint32_t target, uint32_t pckt_seq_nb){
    packet->target = target;
    packet->size = SH_SIZE + payload_size + ECC_SIZE;
    // Fill Service Header (to be removed)
    for (int i = 0; i < (SH_SIZE-2); i++) {
        packet->service_header[i] = i;
    }
    packet->service_header[9] = pckt_seq_nb; // Packet sequence number
    packet->service_header[10] = payload_size; // Payload size
    // Copy Payload to avoid reference
    for (int i = 0; i < payload_size; i++) {
        packet->payload[i] = payload[i];
    }
    
    for (int i = 0; i < ECC_SIZE; i++) { // Iterate over each flit of ecc
        for (int j = 0; j < (SH_SIZE + payload_size)/ECC_SIZE; j=j+2){ // Iterate over each block of flits
            if (j !=  ((SH_SIZE + payload_size)/ECC_SIZE)-1){
                packet->ecc[(j/2) + i*ECC_SIZE] = hamEncode(packet->pkt_payload + j + i*((SH_SIZE + payload_size)/ECC_SIZE), 64, 7);
            } else {
                packet->ecc[(j/2) + i*ECC_SIZE] = hamEncode(packet->pkt_payload + j + i*((SH_SIZE + payload_size)/ECC_SIZE), 32, 6);
            }
        }
    }
}

/**
 * \brief Print Packet struct
 *
 * 
 * \param packet Packet struct input.
 * \param payload_size Packet payload size.
 * \return Void
 */
void print_packet(packet_t packet, uint32_t payload_size){
    printf("Packet:  Target: %u Size: %u Service Header: \n", packet.target, packet.size);
    for (int i = 0; i < SH_SIZE; i++) {
        printf("flit[%d]: %x \n", i, packet.service_header[i]);
    }
    printf("Payload: \n");
    for (int i = 0; i < payload_size; i++) {
        printf("flit[%d]: %x \n", i, packet.payload[i]);
    }
    printf("ECC: ");
    for (int i = 0; i < ECC_SIZE*4; i++) {
        printf("%x ", packet.ecc[i]);
    }
    printf("\n");
}

void connect(connection_t * connection, uint8_t * channel_name, uint8_t * con_type){
    connection->fptr = fopen((char * ) channel_name, (char * )con_type);
    connection->channel_name = channel_name;
}

void close_connect(connection_t * connection){
    fclose(connection->fptr);
}

//@NOTE: It could be better if it was created a method to open the file and other to write or use socket, but
//I do not have time for this right now :).
void send_pckt(packet_t packet, connection_t * connection){
    fwrite(&packet, PACKET_SIZE*4, 1, connection->fptr);
}

//@NOTE: Blocking method
void recv_pckt(packet_t * packet, uint8_t * connection){
    FILE *fptr;
    fptr = fopen((char * ) connection, "r");
    while (!fgets((char *)packet, PACKET_SIZE*4, fptr));
    fclose(fptr);
}
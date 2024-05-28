#include "packet.h"
#include "1_proc_alfa.c"
#include "2_proc_beta.c"
#include "3_inject_error.c"

int main() {
    Packet packet;
    multi_return resultado_packet;
    // Recebe o pacote
    packet=alfa();
    printf("\n");
    // Injeta o erro
    // packet=inject_error(packet);
    resultado_packet=injectErrors(packet,5);
    packet=resultado_packet.packet_error;
    
    // Recebe o pacote
    beta(packet);
    printf("\nNum. Erros: %i",resultado_packet.num_errors);

    // Print auxiliar
    // printf("\n%u %u ", packet.target, packet.size);
    // for (int i = 0; i < SH_SIZE; i++) {
    //     printf("%u ", packet.service_header[i]);
    // }
    // for (int i = 0; i < PAYLOAD_SIZE; i++) {
    //     printf("%u ", packet.payload[i]);
    // }
    // for (int i = 0; i < ECC_SIZE; i++) {
    //     printf("%u ", packet.ecc[i]);
    // }

    return 0;
}

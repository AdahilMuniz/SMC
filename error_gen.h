#ifndef  ERROR_GEN_H
#define  ERROR_GEN_H

    #include <stdlib.h>
    #include <stdio.h>
    #include "packet.h"

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

    void configure_error(packet_t * packet_mask,  error_config_t error_cfg);
    void inject_error(packet_t * packet, packet_t * packet_mask);
    void reset_mask(packet_t * packet_mask);
    void reset_cfg(error_config_t * error_cfg);

    //Scenarios
    void scenario0(packet_t * packet_mask);
    void scenario1(packet_t * packet_mask);

#endif  /*ERROR_GEN_H*/
#include "error_gen.h"

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


//Scenarios
void scenario0(packet_t * packet_mask){
    // No Error
    error_config_t error_cfg;
    error_cfg.error_rand = RAND_NONE;
    error_cfg.field = PAYLOAD_FIELD;
    error_cfg.flit = 0;
    error_cfg.position = 0;
    error_cfg.nb_error = 0;
    configure_error(packet_mask, error_cfg);
}

void scenario1(packet_t * packet_mask){
    // Single Error in only one random flit, field and position
    error_config_t error_cfg;
    error_cfg.error_rand = RAND_FIELD | RAND_FLIT | RAND_POS;
    error_cfg.field;
    error_cfg.flit;
    error_cfg.position;
    error_cfg.nb_error = 1;
    configure_error(packet_mask, error_cfg);
}

void scenario2(packet_t * packet_mask){
    // Double Error in only one random flit, field and positions
    error_config_t error_cfg;
    error_cfg.error_rand = RAND_FIELD | RAND_FLIT | RAND_POS;
    error_cfg.field;
    error_cfg.flit;
    error_cfg.position;
    error_cfg.nb_error = 2;
    configure_error(packet_mask, error_cfg);
}

void scenario3(packet_t * packet_mask){
    // Single Error in two random flit, field and positions
    error_config_t error_cfg;
    error_cfg.error_rand = RAND_FIELD | RAND_FLIT | RAND_POS;
    error_cfg.field;
    error_cfg.flit;
    error_cfg.position;
    error_cfg.nb_error = 1;
    configure_error(packet_mask, error_cfg);

    error_cfg.error_rand = RAND_FIELD | RAND_FLIT | RAND_POS;
    error_cfg.field;
    error_cfg.flit;
    error_cfg.position;
    error_cfg.nb_error = 1;
    configure_error(packet_mask, error_cfg);
}


void scenario4(packet_t * packet_mask){
    // Single Error in n random flit, field and positions
    // n is up to 32 randomly
    error_config_t error_cfg;
    uint32_t n = rand() % 32;

    for (uint32_t i = 0; i < n; i++){
        error_cfg.error_rand = RAND_FIELD | RAND_FLIT | RAND_POS;
        error_cfg.field;
        error_cfg.flit;
        error_cfg.position;
        error_cfg.nb_error = 1;
        configure_error(packet_mask, error_cfg);
    }
}

void scenario5(packet_t * packet_mask){
    // Single Error in SH field and random flit and positions
    error_config_t error_cfg;
    error_cfg.error_rand = RAND_FLIT | RAND_POS;
    error_cfg.field = SH_FIELD;
    error_cfg.flit;
    error_cfg.position;
    error_cfg.nb_error = 1;
    configure_error(packet_mask, error_cfg);
}

void scenario6(packet_t * packet_mask){
    // Single Error in ECC field and random flit and positions
    error_config_t error_cfg;
    error_cfg.error_rand = RAND_FLIT | RAND_POS;
    error_cfg.field = ECC_FIELD;
    error_cfg.flit;
    error_cfg.position;
    error_cfg.nb_error = 1;
    configure_error(packet_mask, error_cfg);
}

uint8_t rand_select_scenario(packet_t * packet_mask){
    uint8_t scne = rand() % SCENARIO_NB;

    switch (scne){
        case 0 : scenario0(packet_mask); break;
        case 1 : scenario1(packet_mask); break;
        case 2 : scenario2(packet_mask); break;
        case 3 : scenario3(packet_mask); break;
        case 4 : scenario4(packet_mask); break;
        case 5 : scenario5(packet_mask); break;
        case 6 : scenario6(packet_mask); break;
        default: scenario0(packet_mask); break;
    }
    
    return scne;
}
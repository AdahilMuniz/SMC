#ifndef  ECC_H
#define  ECC_H

    #include <stdint.h>

    typedef struct {
        uint16_t nb_non_corrected;
        uint16_t nb_corrected;
    } error_t;

    void    encode(uint32_t * data_in, uint32_t * data_out);
    error_t decode(uint32_t * data_in, uint32_t * data_out);

#endif  /*ECC_H*/

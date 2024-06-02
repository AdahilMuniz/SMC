#ifndef  ECC_H
#define  ECC_H

    #include <stdint.h>

    //Mask difines consider 32 bit data
    #define MASK_D1 0b10000000000000000000000000000000
    #define MASK_D(n) (MASK_D1 >> (n-1))
    #define GET_D(n, data) ((data & MASK_D(n)) >> (32-n))

    typedef struct {
        uint16_t nb_non_corrected;
        uint16_t nb_corrected;
    } error_t;

    /*
    typedef union {
        uint32_t data[2];
        uint8_t ecc;
    } hamm64_t;

    typedef union {
        uint32_t data;
        uint8_t ecc;
    } hamm32_t;
    */

    void    encode(uint32_t * data_in, uint32_t * data_out);
    error_t decode(uint32_t * data_in, uint32_t * data_out);

#endif  /*ECC_H*/

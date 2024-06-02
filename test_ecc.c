#include <stdio.h>

#include "ecc.h"

int main () {

    //uint32_t data_in[2] = {0xBEBACAFE, 0xDEADBEEF}; 
    //uint32_t data_err[2] = {0xBFBACAFE, 0xDEADBEEF}; 
    uint32_t data_in[2] = {0x00000000, 0x00000001}; 
    uint32_t data_err[2] = {0x00000000, 0x00000001}; 
    uint8_t ecc;
    error_t err;


    printf("Original: %x %x \n", data_in[0] , data_in[1]);
    printf("Wrong   : %x %x \n", data_err[0], data_err[1]);
    //ecc = hamEncode(data_in, 4, 3);
    //err = hamDecode(data_err, ecc, 4, 3);
    //ecc = hamEncode(data_in, 8, 4);
    //err = hamDecode(data_err, ecc, 8, 4);
    //ecc = hamEncode(data_in, 32, 6);
    //err = hamDecode(data_err, ecc, 32, 6);
    ecc = hamEncode(data_in, 64, 7);
    err = hamDecode(data_err, ecc, 64, 7);

    printf("ECC: %x\n", ecc & 0xFF);
    printf("ERR: %d\n", err);
    printf("Decoded : %x %x \n", data_err[0], data_err[1]);


    return 0;
}
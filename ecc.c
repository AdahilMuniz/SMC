#include "ecc.h"

//@NOTE: For simple hamming code, considering n == word bits number and r == refundancy bits number.
//2^r - 1 >= n, so, for n==64, r==7 and n==32, r==6. For extended hamming code, add one to r result.

//@NOTE (deprected): For code efficiency, we will create two function, one for (72, 64) and another one for (39, 32).
//However, it is always possible to implement a method to search for a r value given an n value. To make
//it easy, the methods will also add the parity bit at the end and will encode the ecc in 8 bits.


uint8_t hamEncode(uint32_t * data_in, uint8_t nb_databits, uint8_t nb_redbits){
    uint8_t ecc = 0;
    uint8_t partial_ecc = 0;
    uint8_t nb_totalbits = nb_databits + nb_redbits;
    uint8_t nb_found_redbits = 0;
    uint8_t flit = 0;

    // Calculating Hamming
    for (uint8_t j = 0; j < nb_redbits; j++){ // Iterate over the reundancy bits
        for (uint8_t i = 1; i <= nb_totalbits; i++){ // Iterate over the entire data (redudancy + data)
            if ( (i & (0b00000001 << j)) &&  (i & (~(0b00000001 << j))) ) { // Check if the referent redundancy bit is set and if it's power of two == it is a parity position
                for (uint8_t k = 0; k < nb_redbits; k++) { // Iterate over the power of two, so we can covert the struct postion to data position 
                    if (i & (0b00000001 << k)){ // Check it already "passed" by a redundancy
                        nb_found_redbits = k +1; // Count the number of redundancy bits already "passed"
                    }
                }
                flit = (uint8_t) ((i-nb_found_redbits)/32);
                partial_ecc ^= GET_D( ((i-nb_found_redbits)%32) , data_in[flit]);
            }
        }
        ecc |= partial_ecc << (7-j);//keep it begining from the MSB
        partial_ecc = 0;
    }

    // Calculating Parity
    for (uint8_t i = 0; i < nb_databits; i++) {
        flit = (uint8_t) (i/32);
        partial_ecc ^= GET_D(i%32, flit);
    }
    for (uint8_t i = 0; i < nb_redbits; i++) {
        partial_ecc ^= ((ecc >> (7-i)) & 0b00000001);
    }
    ecc |= partial_ecc << (7-nb_redbits);//keep it begining from the MSB
    

    return ecc;
}

void encode(uint32_t * data_in, uint32_t * data_out) {

}

error_t decode(uint32_t * data_in, uint32_t * data_out){
    
}
#include "ecc.h"

//@NOTE: For simple hamming code, considering n == word bits number and r == refundancy bits number.
//2^r - 1 >= n, so, for n==64, r==7 and n==32, r==6. For extended hamming code, add one to r result.

//@NOTE: For code efficiency, we will create two function, one for (73, 64) and another one for (39, 32).
//However, it is always possible to implement a method to search for a r value given an n value.


void ham64encode(uint32_t * data_in, uint32_t * data_out){
    uint8_t ecc = 0;

    /*
    ecc = GET_D(1 , data_in[0]) ^ \
          GET_D(2 , data_in[0]) ^ \
          GET_D(4 , data_in[0]) ^ \
          GET_D(5 , data_in[0]) ^ \
          GET_D(7 , data_in[0]) ^ \
          GET_D(9 , data_in[0]) ^ \
          GET_D(11, data_in[0]) ^ \
          GET_D(12, data_in[0]) ^ \
          GET_D(14, data_in[0]) ^ \
          GET_D(14, data_in[0]) ^ \
          GET_D(14, data_in[0]) ^ \
          GET_D(14, data_in[0]) ^ \

      for (uint32_t i = 1; i <= 73; i++){
        
      }
    */
}

void encode(uint32_t * data_in, uint32_t * data_out) {

}

error_t decode(uint32_t * data_in, uint32_t * data_out){
    
}
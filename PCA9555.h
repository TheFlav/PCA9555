#ifndef PCA9555_H
#define PCA9555_H

#include <inttypes.h>  // uint8_t, etc


void PCA9555_write_outputs(uint16_t outputs);
uint16_t PCA9555_read_inputs();
void PCA9555_write_polarity(uint16_t polarity_bits);
void PCA9555_write_direction(uint16_t direction_bits);
int PCA9555_init(uint8_t i2cbusnum, uint8_t i2caddress);
void PCA9555_close(void);


#define PCA9555_IN0         0
#define PCA9555_IN1         1
#define PCA9555_OUT0        2
#define PCA9555_OUT1        3
#define PCA9555_POLARITY0   4
#define PCA9555_POLARITY1   5
#define PCA9555_CONFIG0     6
#define PCA9555_CONFIG1     7




/*
 Command byte
 The command byte is the first byte to follow the address byte during a write transmission.
 It is used as a pointer to determine which of the following registers will be written or read.

 Command        Register
 0              Input port 0
 1              Input port 1
 2              Output port 0
 3              Output port 1
 4              Polarity Inversion port 0
 5              Polarity Inversion port 1
 6              Configuration port 0
 7              Configuration port 1
 */

#endif

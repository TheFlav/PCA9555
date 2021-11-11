#include <stdio.h>
#include <fcntl.h>     // open
#include <linux/i2c-dev.h> // I2C bus definitions
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "PCA9555.h"


int I2CFile = 0;
uint8_t writeBuf[0xFF];      // Buffer to store the 3 bytes that we write to the I2C device
uint8_t readBuf[0xFF];       // Buffer to store the data read from the I2C device




int PCA9555_init(uint8_t i2cbusnum, uint8_t i2caddress)
{
    char devname[55];
    sprintf(devname, "/dev/i2c-%d", i2cbusnum);

    I2CFile = open(devname, O_RDWR);     // Open the I2C device

    ioctl(I2CFile, I2C_SLAVE, i2caddress);   // Specify the address of the I2C Slave to communicate with

    return 0;
}

void PCA9555_write_outputs(uint16_t outputs)
{
    writeBuf[0] = PCA9555_OUT0;
    writeBuf[1] = (outputs & 0xFF);
    writeBuf[2] = ((outputs >> 8) & 0xFF);
    writeBuf[3] = 0;

    write(I2CFile, writeBuf, 3);
}

uint16_t PCA9555_read_inputs()
{
    uint16_t inputs;
    
    writeBuf[0] = PCA9555_IN0;
    writeBuf[1] = 0;

    write(I2CFile, writeBuf, 1);
    
    
    read(I2CFile, readBuf, 2);
    inputs = readBuf[0] | (readBuf[1] << 8);
    
    return inputs;
}

void PCA9555_write_polarity(uint16_t polarity_bits)
{
    writeBuf[0] = PCA9555_POLARITY0;
    writeBuf[1] = (polarity_bits & 0xFF);
    writeBuf[2] = ((polarity_bits >> 8) & 0xFF);
    writeBuf[3] = 0;

    write(I2CFile, writeBuf, 3);
}

void PCA9555_write_direction(uint16_t direction_bits)
{
    //1 = INPUT
    //0 = OUTPUT
    
    writeBuf[0] = PCA9555_CONFIG0;
    writeBuf[1] = (direction_bits & 0xFF);
    writeBuf[2] = ((direction_bits >> 8) & 0xFF);
    writeBuf[3] = 0;

    write(I2CFile, writeBuf, 3);
}

void PCA9555_close(void)
{
    close(I2CFile);
}

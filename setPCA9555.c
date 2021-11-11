#include <stdio.h>
#include <fcntl.h>     // open
#include <inttypes.h>  // uint8_t, etc
#include <stdlib.h>
#include <string.h>
#include <argp.h>

#include <gpiod.h>


#include "PCA9555.h"

char *intpin_chipname = "gpiochip0";
unsigned int intpin_gpio_line = 27;    // GPIO Pin #27


/* Program documentation. */
static char doc[] = "Set PCA9555 via i2c, always use -a, only use one of -l, -p, or -s";

/* A description of the arguments we accept. */
static char args_doc[] = "VALUE";


/* The options we understand. */
static struct argp_option options[] = {
    {"address",  'a', "0xXX",                  0,  "i2c Address of PCA9633" },
    {"i2cbus",   'y', "[0-255]",               0,  "use /dev/i2c-0, /dev/i2c-1, etc. (hint: see i2cdetect command)" },
    { 0 }
};


/* Used by main to communicate with parse_opt. */
struct arguments
{
    uint8_t PCA_i2c_address;
    uint8_t i2cbus;
};


/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
    struct arguments *arguments = state->input;
    
    /*printf("key=%c\n", key);
     if(arg)
     printf("arg=%s\n", arg);*/
    
    switch (key)
    {
        case 'a':
            arguments->PCA_i2c_address = strtoul(arg, NULL, 16);
            break;
        case 'y':
            arguments->i2cbus = strtoul(arg, NULL, 10);
            if(arguments->i2cbus > 255)
                argp_usage (state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}


/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int main (int argc, char **argv)
{
    struct arguments arguments;
    
    /* Default values. */
    arguments.PCA_i2c_address = 0x20;   // Address of our device on the I2C bus
    arguments.i2cbus = 74;
    
    /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);
    
    printf ("I2CBUS = %d CHIPADDR = 0x%02X\n",            arguments.i2cbus,   arguments.PCA_i2c_address);
    
    
    if(PCA9555_init(arguments.i2cbus, arguments.PCA_i2c_address) != 0)
    {
        printf("Error initializing i2c bus %d.\n", arguments.i2cbus);
        return EXIT_FAILURE;
    }
    
    
    {
        struct gpiod_chip *chip;
        struct gpiod_line *line;
        int req, value;

        chip = gpiod_chip_open_by_name(intpin_chipname);
        if (!chip)
        {
            printf("Error: gpiod_chip_open_by_name\n");
            return -1;
        }

        line = gpiod_chip_get_line(chip, intpin_gpio_line);
        if (!line) {
            printf("Error: gpiod_chip_get_line\n");
            gpiod_chip_close(chip);
            return -1;
        }

        req = gpiod_line_request_input(line, "pca9555 nINT");
        if (req) {
            printf("Error: gpiod_line_request_input\n");
            gpiod_line_release(line);
            gpiod_chip_close(chip);
            return -1;
        }

        while(1)
        {
            value = gpiod_line_get_value(line);
            if(value == 0)
            {
                uint16_t inputs = PCA9555_read_inputs();
                
                printf("INPUTS = 0x%04X\n", inputs);
            }
        }


        gpiod_line_release(line);
        gpiod_chip_close(chip);
    }
    
    
        
    return EXIT_SUCCESS;
}

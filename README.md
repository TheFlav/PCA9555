# setPCA9633
Set PCA9633 via I2C on Raspberry Pi. Includes installation for a backlight and PWM fan controller for Freeplay units. It should be noted that the PWM Fan control requires the Freeplay L2/R2 Addon board, with the pin 40 pad on the Addon board soldered to the large pad on the main PCB to the left of the CM3 connector.

### Compilation and Usage
```sh
sudo raspi-config #under interface options, enable I2C and reboot
git clone https://github.com/theFlav/setPCA9633
cd setPCA9633
make
./install.sh #if using with Freeplay unit with backlight/fan control
```

#### Arguments

| Argument Flag   | Possible Values             | Description                                                                       |
| :-------------: | :-------------------------- | ----------------------------------------------------------------------            |
| `a`             | `0xXX`                      | I2C Address of PCA9633                                                            |
| `y`             | `0`, `1`                    | Use `/dev/i2c-0` or `/dev/i2c-1` (hint: see `man i2cdetect`)                      |
| `l`             | `ON`, `OFF`, `PWM`, `GRP`   | Set led0 to `ON`, `OFF`, `PWM`, or `GRP`                                          |
| `m`             | `ON`, `OFF`, `PWM`, `GRP`   | Set led1 to `ON`, `OFF`, `PWM`, or `GRP`                                          |
| `n`             | `ON`, `OFF`, `PWM`, `GRP`   | Set led2 to `ON`, `OFF`, `PWM`, or `GRP`                                          |
| `o`             | `ON`, `OFF`, `PWM`, `GRP`   | Set led3 to `ON`, `OFF`, `PWM`, or `GRP`                                          |
| `p`             | `0xXX`                      | Set pwm0 to `0xXX` (Hexadecimal value, hence the 0x)                              |
| `q`             | `0xXX`                      | Set pwm1 to `0xXX`                                                                |
| `r`             | `0xXX`                      | Set pwm2 to `0xXX`                                                                |
| `s`             | `0xXX`                      | Set pwm3 to `0xXX`                                                                |
| `g`             | `0xXX`                      | Set grppwm to `0xXX` (Duty cycle, out of 0xFF or 255)                             |
| `h`             | `0xXX`                      | Set grpfreq to `0xXX` (Smaller is for higher frequency, 0xFF is 10 second period) |
| `1`             | `0xXX`                      | Set mode1 to `0xXX`                                                               |
| `2`             | `0xXX`                      | Set mode1 to `0xXX`                                                               |
| `w`             | `WAKE`, `SLEEP`             | `WAKE` or `SLEEP` (no output during `SLEEP`)                                      |
| `i`             | `NO`, `YES`                 | Invert PWM? YES/NO                                                                |
| `d`             | `OFF`, `ON`                 | OUTDRV on? OFF/ON                                                                 |
| `b`             | `OFF`, `ON`                 | DMBLNK on? OFF=dimming/ON=blinking                                                |
| `v`             | `0`,`1`,`2`                 | 0=no output  1=only output exitcode 2=normal full output                          |
| `e`             | `0`,`1`,`2`,`3`             | Use current LEDn value as exitcode when done                                      |

So, as an example:
```sh
./setPCA9633 -y 1 -a 0x62 -d ON -w WAKE -i YES -m GRP -h 0x08 -g 0x30 -b ON
#           └──┬─┘└───┬─┘ └─┬─┘ └───┬──┘└─┬──┘ └───┬┘ └─┬──┘ └─┬───┘ └─┬─┘
#           i2cbus 1  │  outdrv ON  │  invert PWM  │ GRP Freq  │  Blinking mode
#     i2c address 0x62┘ wake up chip┘  CH1 GRP mode┘ Duty Cycle┘
```
# PCA9555

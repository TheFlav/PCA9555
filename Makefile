all : setPCA9555

setPCA9555 : setPCA9555.c PCA9555.c PCA9555.h
	gcc -O3 -o setPCA9555 -lgpiod PCA9555.c setPCA9555.c


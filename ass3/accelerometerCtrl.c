#include "accelerometerCtrl.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <time.h>
#include "audioMixer_template.h"


#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"

#define I2C_DEVICE_ADDRESS 0x1C

#define REG_DIR 0x2A
#define REG_OUT 0x01

#define THRESHOLD_X 5000
#define THRESHOLD_Y 5000
#define THRESHOLD_Z 4


#define BASE_DRUM 0
#define SNART 1
#define STYU 2


static unsigned char OUT_X_MSB = 0x00;
static unsigned char OUT_X_LSB = 0x00;
static unsigned char OUT_Y_MSB = 0x00;
static unsigned char OUT_Y_LSB = 0x00;
static unsigned char OUT_Z_MSB = 0x00;
static unsigned char OUT_Z_LSB = 0x00;

static int i2cFileDesc=0;

int16_t prevX=0;
int16_t prevY=0;
int16_t prevZ=0;

static int initI2cBus(char* bus, int address)
{
	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is:");
		exit(-1);
	}

	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("Unable to set I2C device to slave address.");
		exit(-1);
	}
	return i2cFileDesc;
}


static void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value)
{
	unsigned char buff[2] = {regAddr, value};
	int res = write(i2cFileDesc, buff, 2);
	if (res != 2) {
		perror("Unable to write i2c register");
		exit(-1);
	}
}




void accelerometer_init(){
	i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
	writeI2cReg(i2cFileDesc, REG_DIR, REG_OUT);
	update_postionVal();
	close(i2cFileDesc);
}

void update_postionVal(){

	const int noOfBytes=7;
	char value[noOfBytes];
	i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);


	int res = read(i2cFileDesc, &value, sizeof(value));
	if (res != sizeof(value)) {
		perror("Unable to read i2c register");
		exit(-1);
	}

	OUT_X_MSB = value[1];
	OUT_X_LSB = value[2];
	OUT_Y_MSB = value[3];
	OUT_Y_LSB = value[4];
	OUT_Z_MSB = value[5];
	OUT_Z_LSB = value[6];

	int16_t x = (OUT_X_MSB << 8) | (OUT_X_LSB);
	int16_t y = (OUT_Y_MSB << 8) | (OUT_Y_LSB);
	int16_t z = (((OUT_Z_MSB << 8) | (OUT_Z_LSB))-16300)/1000;


	if(prevX!=0 && abs(prevX-x)>THRESHOLD_X){
		Audio_playFile(BASE_DRUM);
	}

	if(prevY!=0 && abs(prevY-y)>THRESHOLD_Y){
		Audio_playFile(SNART);
	}

	if(prevZ!=0 && abs(prevZ-z)>THRESHOLD_Z){
		Audio_playFile(BASE_DRUM);
	}

	prevX=x;
	prevY=y;
	prevZ=z;

	printf("%i\n",z);

//	printf("x: %i, y: %i, z: %i\n",x,y,z);
//	printf("%02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x\n", value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7], value[8], value[9]);
//	nanosleep((const struct timespec[]){{0, 100000000}}, NULL);

	close(i2cFileDesc);
}

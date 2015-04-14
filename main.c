#define YAW_THRESHOLD 0

#include "matrix_display.h"

struct led_matrix game;
game.leds = {{0}};

int main(void)
{
	/* send init commands to accelerometer */
	mpu6050_dmpInitalize();
	mpu6050_dmpEnable();

	sei();
}

/* ISR to refresh screen */
ISR(/* timer */)
{
	show(game.leds);
}

/* ISR to update game */
ISR(/* timer */)
{
	if(yaw > YAW_THRESHOLD)
	{
		/* move player right */
	}
	else if(yaw < -1*YAW_THRESHOLD)
	{
		/* move player left */
	}
	else
	{
		/* do not move player */
	}
}

/* ISR to fetch sensor data */
ISR(/* sensor data ready */)
{
	/* save values in global variables */
	mpu6050_getRollPitchYaw(...);
}
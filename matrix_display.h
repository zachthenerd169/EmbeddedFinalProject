#define RED_BIT 0
#define GREEN_BIT 1
#define BLUE_BIT 2

struct led_matrix
{
	char leds[8][8]; 
};

void show(struct led_matrix leds)
{
	/* load and display each row one at a time */
	char cur_led;
	char red;
	char green;
	char blue;
	reset_column();
	for(int rr = 0; rr < 8; rr++)
	{
		for(int cc = 0; cc < 8; cc++)
		{
			cur_led = leds.leds[rr][cc];

			red = (cur_led & (1 << RED_BIT)) != 0;
			green = (cur_led & (1 << GREEN_BIT)) != 0;
			blue = (cur_led & (1 << BLUE_BIT)) != 0;

			shift_rgb(red, green, blue);
		}

		/* latch row and column */
		/* delay */
		/* unlatch row and column */
		
		advance_column();
	}
}

void clear(struct led_matrix *leds)
{
	memset(leds->leds,0,sizeof(leds->leds)); // may or may not work on avr
}

void shift_rgb(char r, char g, char b)
{
	//set r, g, and b shift register data lines

	//cycle clock
}

void reset_column()
{
	/* cycle clock on column register 8 times */

	/* set data high */

	/* cycle clock */

	/* set data low */
} 

void advance_column()
{
	/* cycle clock */
}
/* Define player values */
#define P1 1
#define P2 2
/* Define shift register ports */
#define BLUE_DATA_PIN 0
#define GREEN_DATA_PIN 0
#define COLOR_CLOCK_PIN 0
#define SHIFT_DATA_PORT PORTB
#define COMMON_DATA_PIN 0
#define SHIFT_SHOW_PIN 0
#define COLOR_SHOW_PIN 0

/* Define timing constants */
#define CYCLE_CLOCK_DELAY_MS 2
#define SHIFT_DATA_DELAY_MS 2

char board[9] = {0,0,0,
				 0,0,0,
				 0,0,0};
char cursor = 0;

void drawBoard()
{
	for(int DRow = 0; DRow < 8; ++DRow)
	{
		/* send color data to row */
		switch(DRow)
		{
			case 0:
			case 1:
				shiftOut(cursor == 0 ? 2 : board[0])
				shiftOut(cursor == 0 ? 2 : board[0])
				shiftOut(2);
				shiftOut(cursor == 1 ? 2 : board[1])
				shiftOut(cursor == 1 ? 2 : board[1])
				shiftOut(2);
				shiftOut(cursor == 2 ? 2 : board[2])
				shiftOut(cursor == 2 ? 2 : board[2])
				break;
			case 3:
			case 4:
				shiftOut(cursor == 3 ? 2 : board[3])
				shiftOut(cursor == 3 ? 2 : board[3])
				shiftOut(2);
				shiftOut(cursor == 4 ? 2 : board[3])
				shiftOut(cursor == 4 ? 2 : board[3])
				shiftOut(2);
				shiftOut(cursor == 5 ? 2 : board[3])
				shiftOut(cursor == 5 ? 2 : board[3])
				break;			
			case 6:
			case 7:
				shiftOut(cursor == 6 ? 2 : board[3])
				shiftOut(cursor == 6 ? 2 : board[3])
				shiftOut(2);
				shiftOut(cursor == 7 ? 2 : board[3])
				shiftOut(cursor == 7 ? 2 : board[3])
				shiftOut(2);
				shiftOut(cursor == 8 ? 2 : board[3])
				shiftOut(cursor == 8 ? 2 : board[3])
				break;
			case 2:
			case 5:
				shiftOut(2);
				shiftOut(2);
				shiftOut(2);
				shiftOut(2);
				shiftOut(2);
				shiftOut(2);
				shiftOut(2);
				shiftOut(2);
		}
		/* TODO: 
		 *  move row down
		 *  -> cycle row clock
		 *  -> show row (common)
		 *  show row
		 *  -> show row (color)
		 */
	}
}

void shiftOut(unsigned char data)
{
	/* data = G | B (=G+B)
	 * green = 1
	 * blue  = 2
	 * both  = 3
	 */

	/* get inverted bits */
	char Gbit = (~data & 1) !=0;
	char Bbit = (~data & 2) !=0;

	/* send bits to shift register data pins */
	SHIFT_DATA_PORT |= (Gbit << GREEN_DATA_PIN) | (Bbit << BLUE_DATA_PIN);
	delay_ms(SHIFT_DATA_DELAY_MS);

	/* cycle shift register clock */
	SHIFT_DATA_PORT |= (1 << COLOR_CLOCK_PIN);
	delay_ms(CYCLE_CLOCK_DELAY_MS);
	SHIFT_DATA_PORT &= ~(1 << COLOR_CLOCK_PIN);
}
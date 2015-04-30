/********************************
Positions:
 0 | 1 | 2
 ---------
 3 | 4 | 5
 ---------
 6 | 7 | 8
*********************************/

char board[9] = {0,0,0,
				 0,0,0,
				 0,0,0};

double roll = 0;
double pitch = 0;
#define TILT_THRESHOLD 20
#define N_TILT_THRESHOLD (0-TILT_THRESHOLD)
// cursor hold time is how long (in seconds) the user needs to hold the cursor at a position for it to set
#define CURSOR_HOLD_TIME 5
// timer threshold is the number of clock cycles that correspond to the cursor hold time on an 8x prescaled clock
#define TIMER_THRESHOLD (CURSOR_HOLD_TIME*F_CPU/8)

int cursor = 4;
int cursorOld = 4;

int currentPlayer = 1;

int waiting = 0;

unsigned long timer = 0;


inline int getPosition()
{
	if(roll > N_TILT_THRESHOLD)
	{
	    if(pitch < N_TILT_THRESHOLD)
		{
	 		return 0;
	 	}
	 	if(pitch > TILT_THRESHOLD)
	 	{
	 		return 2;
	 	}
	 	return 1;
	}
	if(roll < N_TILT_THRESHOLD)
	{
	 	if(pitch < N_TILT_THRESHOLD)
	 	{
	 		return 6;
	 	}
	 	if(pitch > TILT_THRESHOLD)
	 	{
	 		return 8;
	 	}
	 	return 7;
	}
	if(pitch < N_TILT_THRESHOLD)
	{
		return 3;
	}
	if(pitch > TILT_THRESHOLD)
	{
		return 5;
	}
	return 4;
}

inline void updateCursor()
{
	cursor = getPosition();
}

inline void updateTimer()
{
	if(cursor != cursorOld)
	{
		timer = 0;
	}
	else if(board[cursor] != 0)
	{
		timer = 0;
	}
	else if(board[cursor] == currentPlayer)
	{
		timer = 0;
	}

	timer++;
}

int updateBoard()
{
	updateCursor();
	updateTimer();

	if(timer > TIMER_THRESHOLD)
	{
		board[cursor] = currentPlayer; // place player at space
		currentPlayer = 3-currentPlayer; // switch players (1 -> 2 ; 2 -> 1)
		timer  = 0; // reset timer
	}
}
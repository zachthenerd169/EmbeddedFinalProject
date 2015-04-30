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
// calculate a count for delaying x seconds on an 8x prescaled clock trigger interrupt
#define TIMER_DELAY_S(x) (x*F_CPU/8)

int cursor = 4;
int cursorOld = 4;

int currentPlayer = 1;
int winner = 0;

unsigned long timer = 0;

int winSequenceState = 0;


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
	cursorOld = cursor;
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

int checkWin(int cursorPos)
{
	if(board[cursorPos] == 0)
	{
		return 0;
	}

	/* top row */
	if(cursorPos < 3 && board[0] == board[1] && board[1] == board [2])
	{
		return board[0];
	}
	/* middle row */
	if((cursorPos < 6 && cursorPos > 2) && board[3] == board[4] && board[4 == board[5])
	{
		return board[3];
	}
	/* bottom row */
	if((cursorPos < 9 && cursorPos > 5) && board[6] == board[7] && board[7] == board[8])
	{
		return board[6];
	}
	/* left column */
	if((cursorPos % 3 == 0) && board[0] == board[3] && board[3] == board[6])
	{
		return board[0];
	}
	/* middle column */
	if((cursor % 3 == 1) && board[1] == board[4] && board[4] == board[7])
	{
		return board[1];
	}
	/* right column */
	if((cursor % 3 == 2) && board[2] == board[5] && board[5] == board[8])
	{
		return board[2];
	}
	/* \ diagonal */
	if((cursor % 4 == 0) && board[0] == board[4] && board[4] == board[8])
	{
		return board[0];
	}
	/* / diagonal */
	if((cursor % 2 == 0 && cursor < 8) && board[2] == board[4] && board[4] == board[6])
	{
		return board[2];
	}

	/* no winner found */
	return 0;
}

void winSequence()
{
	/* just entered win sequence */
	if(winSequenceState == 0)
	{
		timer = 0;
		winSequenceState = 1;
	}
	/* do a short delay */
	else if(winSequenceState == 1)
	{
		timer++;
		if(timer > TIMER_DELAY_S(3))
		{
			winSequenceState = 2;
		}
	}
	/* clear all non winning pieces */
	else if(winSequence == 2)
	{
		int i = 0;
		for(i = 0; i< 9; i++)
		{
			if(board[i] != winner)
			{
				board[i] = 0;
			}
		}
		winSequenceState = 3;
		timer=0;
	}
	/* do a short delay */
	else if(winSequenceState == 3)
	{
		timer++;
		if(timer > TIMER_DELAY_S(7))
		{
			winSequenceState = 4;
		}
	}
	/* reset and restart game */
	else if(winSequenceState == 4)
	{
		cursor = 4;
		cursorOld = 4;
		timer = 0;
		winner = 0;
		currentPlayer = 3-winner; //loser gets to start
		winSequenceState = 0;
	}
}

int updateBoard()
{
	if(winner != 0){
		updateCursor();
		updateTimer();

		if(timer > TIMER_DELAY_S(5))
		{
			board[cursor] = currentPlayer; // place player at space
			winner = checkWin();
			if(winner == 0)
			{
				currentPlayer = 3-currentPlayer; // switch players (1 -> 2 ; 2 -> 1)
			}
			timer = 0; // reset timer
		}
	}
	else
	{
		cursor = -1;
		winSequence();
	}
}
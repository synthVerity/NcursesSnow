#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

// Struct that holds placement information for each snowflake
struct snow
{
	int x;
	int y;
};

// Obvious main is obvious
int main(int argc, char *argv[])
{

	// All the variables used, including the array of snowflakes
	int i;
	int running = 1, AIplayer = 0;
	int maxY, maxX;
	int playX, playY;
	char piece = '*';
	char player = '#';
	int numSnowflakes;

	// Set the number of snowflakes used in the game
	if(argc > 1)
	{
		numSnowflakes = atoi(argv[1]);
	}
	else
	{
		numSnowflakes = 50;
	}

	struct snow snowflakes[numSnowflakes];

	// Seed random
	srand(time(NULL));

	// Start the ncurses library, stdscr
	initscr();

	// Ncurses values used to set various settings
	keypad(stdscr, TRUE);
	halfdelay(1);
	curs_set(0);

	// Get size of terminal used for program
	getmaxyx(stdscr, maxY, maxX);

	playY = maxY - 1;
	playX = maxX / 2;

	// Initialize the snowflake locations
	for(i = 0; i < numSnowflakes; i++)
	{
		snowflakes[i].x = rand() % maxX;
		snowflakes[i].y = rand() % maxY;
	}

	// Main animation loop
	while(running)
	{
		clear();

		// Output of the clouds
		for(i = 0; i < maxX; i++)
		{
			mvprintw(0, i, "&");
		}

		// Output of the individual snowflakes
		for(i = 0; i < numSnowflakes; i++)
		{
			mvprintw(snowflakes[i].y, snowflakes[i].x, "%c", piece);

			// Sets another on the top when snowflakes reach the bottom of the screen
			if(snowflakes[i].y > maxY)
			{
				snowflakes[i].x = rand() % maxX;
				snowflakes[i].y = 0;
			}

			// To simulate a snowflake falling
			snowflakes[i].y++;
		}

		// Output of player piece
		mvprintw(playY, playX, "%c", player);

		// User input to cancel the program and move the player piece
		switch(getch())
		{
			case KEY_F(1):
				running = 0;
				break;

			case KEY_F(2):
				AIplayer = 1;
				break;

			case KEY_LEFT:
				if(playX <= 0)
					break;

				playX--;

				break;

			case KEY_RIGHT:
				if(playX >= maxX - 1)
					break;

				playX++;

				break;

		}

		// If a snowflake appears above the game piece,
		// the computer moves it out of the way. Should be a perfect win
		if(AIplayer)
		{
			for(i = 0; i < numSnowflakes; i++)
			{
				if(snowflakes[i].x == playX && playX > 0)
					playX--;
				else if(snowflakes[i].x == playX)
					playX++;
			}
		}

		// Collision check for snowflake
		for(i = 0; i < numSnowflakes; i++)
		{
			if(playX == snowflakes[i].x && playY == snowflakes[i].y - 1)
			{
				running = 0;
			}
		}

	}

	// Ends ncurses and the initial program
	endwin();
	return 0;
}

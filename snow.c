#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define SNOWFLAKES 50

// Struct that holds placement information for each snowflake
struct snow
{
	int x;
	int y;
};

// Obvious main is obvious
int main(void)
{
	// All the variables used, including the array of snowflakes
	int i;
	int running = 1;
	int maxY, maxX;
	char piece = '*';
	struct snow snowflakes[SNOWFLAKES];

	// Seed random
	srand(time(NULL));

	// Start the ncurses library, stdscr
	initscr();

	// Ncurses values used to set various settings
	keypad(stdscr, TRUE);
	halfdelay(1);
	curs_set(0);

	getmaxyx(stdscr, maxY, maxX);

	// Initialize the snowflake locations
	for(i = 0; i < SNOWFLAKES; i++)
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
		for(i = 0; i < SNOWFLAKES; i++)
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

		// User input to cancel the program
		switch(getch())
		{
			case KEY_F(1):
				running = 0;
				break;
		}

	}

	// Ends ncurses and the initial program
	endwin();
	return 0;
}

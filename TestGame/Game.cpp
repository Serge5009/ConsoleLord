#include "Game.h"
#include "Timer.h"
#include "Player.h"
#include <conio.h>
#include <SDL.h>
#include <iostream>

using namespace std;

Game::Game()
{
	StartingScreen();	//	Calling the starting screen

}

Game::~Game()
{

	
}

void Game::Start()
{
	isRunning = true;	//	Activate main game loop
	isPlaying = true;	//	Unpause

	GameSpeed = 3;		//	Set game speed to normal

	day = 0;			//	We start with day 0

	GameLoop();			//	Enters the game loop
}

void Game::GameLoop()
{
	Timer deltaTimer;	//	Creates a timer to control time between updates
	deltaTimer.Start();	//	We will use it later to adjust int gameSpeed

	while (isRunning)
	{
		HandleEvents();	//	Event handler (input)

		if(isPlaying)		//	This function contains all actions happening in the game
		Update();	//	If game is paused we won't call it
							//	But input and render will still be called

							//	Assigns time that passed between loops to variable
		deltaTime = static_cast<float>(deltaTimer.GetTicks()) / 1000.0f;
		deltaTimer.Start();	//	Starts timer again
		
		Render();			//	Renders selected settlement or menu

							//	Assigns proper freeze time in ms according to selected speed
		switch (GameSpeed)
		{
		case 1:
			gameSpeed = 5000;
			break;
		case 2:
			gameSpeed = 2000;
			break;
		case 3:
			gameSpeed = 1000;
			break;
		case 4:
			gameSpeed = 500;
			break;
		case 5:
			gameSpeed = 100;
			break;
		default:
			break;
		}
							//	Freezes loop
		SDL_Delay(gameSpeed);
	}
}

	//	Input handler
void Game::HandleEvents()
{	
	while (_kbhit())		//	Ignores the loop if no keys were pressed
	{
		int key = _getch();	//	Assigns ID of entered symbol to key variable
		//	Goes through all possible keys
		if (key == ' ') {	//	SPACE for pause/unpause
			isPlaying = !isPlaying;
		}
		if (key == '=') {	//	+ for speed up
			GameSpeed++;
			if (GameSpeed > 5)
				GameSpeed = 5;
		}
		if (key == '-') {	//	-	for slow down
			GameSpeed--;
			if (GameSpeed < 1)
				GameSpeed = 1;
		}
	}
}

void Game::Update()
{ 
	player.Update();	//	Calls player's function that handles update

	//	here will be the loop that calls .Update() for all AI

	day++;		//	Add one day to counter
}

void Game::Render()
{
	system("CLS");		//	Clear the screen
						//	Renders top bar
	cout << "\tMoney " << player.money << "\t\t\tDay " << day;
	if (isPlaying)	//	Outputs speed
		cout << "\t\t\tSpeed " << GameSpeed;
	else			//	or "PAUSED" if game is paused
		cout << "\t\t\tPAUSED";
	cout << endl;

		//	Here will be the code to render the selected menu or settlement
	player.RenderSett(0);		//	For now it renders main player settlement
	cout << "\n\n\ndeltaTime: " << deltaTime << endl;	//	DEBUG	//	Outputs time between loops
}


	//	Outputs starting screen and handles input
void Game::StartingScreen()
{
	bool startLoop = true;		//	Loop control
	bool isYesSelected = true;	//	Selected option
	while (startLoop)
	{
		system("CLS");	//	Clear screen
		cout << "\n\n\n\n\n\n\n";
		cout << "\t\t\t\t\t   Welcome to Console Lord" << endl << endl << endl;
		cout << "\t\t\t\t\t    Wanna start the game?" << endl << endl;
		cout << "\t\t\t\t\t\t";

		//	Highlites selected option
		if (isYesSelected)
			cout << "\033[102m";	//	make BG Green
		cout << "Yes";
		if (isYesSelected)
			cout << "\033[40m";		//	restore BG color
		cout << "\t";
		if (!isYesSelected)
			cout << "\033[102m";	//	make BG Green
		cout << "No" << endl;
		if (!isYesSelected)
			cout << "\033[40m";		//	restore BG color

		cout << "\n\n\n\n\n";
		cout << "\tUse 'a' and 's' to navigate," << endl;
		cout << "\tUse 'd', SPACE or ENTER to select." << endl;
		
		while (_kbhit())	//	Simple input system
		{
			int key = _getch();
			if (key == 'a') {	//	a for left
				isYesSelected = true;
			}
			if (key == 'd') {	//	d for right
				isYesSelected = false;
			}
			if (key == ' ') {	//	SPACE to proceed
				startLoop = false;
			}
			if (key == 'e') {	//	e to proceed
				startLoop = false;
			}
			if (key == '\r') {	//	ENTER to proceed
				startLoop = false;
			}
		}

		SDL_Delay(100);	//	Slow down render of the screen
	}
	if (isYesSelected)	//	Was yes pressed?
	{
		HelpScreen();	//	Show info & controls 
		Start();		//	Start the game
	}
	else				//	User doesn't want to play our game( 
	{
		cout << "\n\n\nC'ya later, stranger!" << endl;
		Stop();			//	This will avoid entering the main game loop
	}
}

	//	Outputs help screen and freezes game until any key is pressed
void Game::HelpScreen()
{
	system("CLS");	//	Clear screen

	cout << "\n\n";	//	Output content
	cout << "\tConsole Lord is a strategy game, where you have to manage one or more" << endl;
	cout << "\tsettlement's that you own. Each of them have their peculiar properties" << endl;
	cout << "\tthat define their strong and week sides. Build proper buildings and maintain" << endl;
	cout << "\ttrade routes to make your kingdom grow!" << endl << endl;
	cout << "\tGather your troops to fight your enemies and expand your territory!" << endl << endl << endl;
	cout << "Controls:" << endl;
	cout << "\tWASD for navigation" << endl;
	cout << "\t'e' or ENTER for selection" << endl;
	cout << "\tSPACE for pause/unpause" << endl;
	cout << "\t+ to speed up / - to slow down" << endl << endl << endl;
	cout << "\t\tpress any key to proceed" << endl;

	while (!_kbhit()) {}	//	Waiting for any input
}




			//	Global random functions

	//	Returns nubmer between min and max
int RandomRange(int min, int max)
{
	if (isFirstTimeSeed)
	{
		srand(time(NULL));
		isFirstTimeSeed = false;
	}

	return (rand() % (max - min + 1)) + min;
}

	//	Returns one of two inputed values
int ChooseRandom(int one, int two)
{
	if (isFirstTimeSeed)
	{
		srand(time(NULL));
		isFirstTimeSeed = false;
	}
	if (rand() % 2 == 0)
		return one;
	if (rand() % 2 == 1)
		return two;
}
	//	(overloaded) Returns one of three inputed values
int ChooseRandom(int one, int two, int three)
{
	if (isFirstTimeSeed)
	{
		srand(time(NULL));
		isFirstTimeSeed = false;
	}
	if (rand() % 3 == 0)
		return one;
	if (rand() % 3 == 1)
		return two;
	if (rand() % 3 == 2)
		return three;
}
#include "Game.h"
#include "Timer.h"
#include "Player.h"
#include <conio.h>
#include <SDL.h>
#include <iostream>

using namespace std;

Game::Game()
{
	StartingScreen();
	isRunning = true;
	isPlaying = true;
	GameSpeed = 3;
	deltaTime = 1.0;
	
	day = 0;
}

Game::~Game()
{

	
}

void Game::Start()
{
	HelpScreen();

	isRunning = true;
	
	GameLoop();
	
}

void Game::GameLoop()
{
	Timer deltaTimer;
	deltaTimer.Start();

	while (isRunning)
	{
		HandleEvents();

		if(isPlaying)
		Update(deltaTime);

		deltaTime = static_cast<float>(deltaTimer.GetTicks()) / 1000.0f;
		deltaTimer.Start();
		
		Render();

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
		SDL_Delay(gameSpeed);
	}

}
	//	Pause doesn't work
void Game::HandleEvents()
{
	while (_kbhit())
	{
		int key = _getch();
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

void Game::Update(float DeltaTime)
{ 
	player.Update();

	day++;
}

void Game::Render()
{
	system("CLS");
	cout << "\tMoney " << player.money << "\t\t\tDay " << day;
	if (isPlaying)
		cout << "\t\t\tSpeed " << GameSpeed;
	else
		cout << "\t\t\tPAUSED";
	cout << endl;
	player.RenderSett(0);
	cout << "\n\n\ndeltaTime: " << deltaTime << endl;
}


//	Outputs starting screen and handles input
void Game::StartingScreen()
{
	bool startLoop = true;		//	Loop control
	bool isYesChoosen = true;	//	Selected option
	while (startLoop)
	{
		system("CLS");
		cout << "\n\n\n\n\n\n\n";
		cout << "\t\t\t\t\t   Welcome to Console Lord" << endl << endl << endl;
		cout << "\t\t\t\t\t    Wanna start the game?" << endl << endl;
		cout << "\t\t\t\t\t\t";
		if (isYesChoosen)
			cout << "\033[102m";	//	make BG Green
		cout << "Yes";
		if (isYesChoosen)
			cout << "\033[40m";	//	restore BG color
		cout << "\t";
		if (!isYesChoosen)
			cout << "\033[102m";	//	make BG Green
		cout << "No" << endl;
		if (!isYesChoosen)
			cout << "\033[40m";	//	restore BG color
		cout << "\n\n\n\n\n";
		cout << "\tUse 'a' and 's' to navigate," << endl;
		cout << "\tUse 'd', SPACE or ENTER to select." << endl;
		
		while (_kbhit())	//	Simple input system
		{
			int key = _getch();
			if (key == 'a') {	//	a for left
				isYesChoosen = true;
			}
			if (key == 'd') {	//	d for right
				isYesChoosen = false;
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

		SDL_Delay(100);
	}
	if (isYesChoosen)
	{
		Start();
	}
	else
	{
		cout << "\n\n\nC'ya later, stranger!" << endl;
		Stop();
	}
}

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
int RandomRange(int min, int max)
{
	if (isFirstTimeSeed)
	{
		srand(time(NULL));
		isFirstTimeSeed = false;
	}

	return (rand() % (max - min + 1)) + min;
}

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
#include "Game.h"
#include "Timer.h"
#include "Player.h"
#include <conio.h>
#include <SDL.h>
#include <iostream>

using namespace std;

Game::Game()
{
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
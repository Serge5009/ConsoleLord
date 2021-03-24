#include "Game.h"
#include "Timer.h"
#include <SDL.h>
#include <iostream>

Game::Game()
{
	isRunning = true;
	deltaTime = 1.0;

}

Game::~Game()
{

	delete[] PlayerSett;
}

void Game::Start()
{
	isRunning = true;

	delete PlayerSett;
	PlayerSett = new Settlement[1];
	PlayerSett[0].ID = 0;
	SettAmount = 1;
	PlayerSett[0].CoutSett();
	GameLoop();
	
}

void Game::GameLoop()
{
	Timer deltaTimer;
	deltaTimer.Start();

	while (isRunning)
	{
		HandleEvents();

		Update(deltaTime);

		deltaTime = static_cast<float>(deltaTimer.GetTicks()) / 1000.0f;
		deltaTimer.Start();
		
		Render();
		SDL_Delay(gameSpeed);
	}

}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		Stop();
		break;
	}
}

void Game::Update(float DeltaTime)
{ 
	PlayerSett[0].Update();
}

void Game::Render()
{
	PlayerSett[0].CoutSett();
	std::cout << deltaTime << std::endl;
}

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
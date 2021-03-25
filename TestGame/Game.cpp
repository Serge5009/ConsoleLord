#include "Game.h"
#include "Timer.h"
#include "Player.h"
#include <SDL.h>
#include <iostream>

Game::Game()
{
	isRunning = true;
	isPlaying = true;
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
		SDL_Delay(gameSpeed);
	}

}
	//	Pause doesn't work
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

	switch (event.key.keysym.sym)
	{
	case SDLK_SPACE:
	{
		isPlaying = !isPlaying;
		std::cout << "PAUSED!" << std::endl;
		SDL_Delay(100);
		break;
	}
	default:
		break;
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
	std::cout << "\tMoney " << player.money << "\t\t\tDay " << day << std::endl;
	player.RenderSett(0);
	std::cout << "\n\n\ndeltaTime: " << deltaTime << std::endl;
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
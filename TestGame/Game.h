#pragma once

#include<cstdlib>
#include<ctime>
#include "Player.h"

class Game
{
private:
	bool isRunning;	//	Controls Game loop
	bool isPlaying;	//	If false - freezes updates
	float deltaTime;	//	Time in ms passed between loops
	short GameSpeed;	//	Game speed from 1 to 5
	int gameSpeed = 999;	//	Freeze time in ms between loops

	int day;	//	Global day counter

	//	Main game loop, takes 1 second
	void GameLoop();
	void HandleEvents();
	void Update(float DeltaTime);
	void Render();

public:
	//	Constructor
	Game();
	//	Destructor
	~Game();

	Player player;

	//	Starts Game
	void Start();
	//	Stop Game
	void Stop() { isRunning = false; }
	
	
	int SettAmount = 0;
};


//	Random
static bool isFirstTimeSeed = true;

int RandomRange(int min, int max);
int ChooseRandom(int one, int two);
int ChooseRandom(int one, int two, int three);
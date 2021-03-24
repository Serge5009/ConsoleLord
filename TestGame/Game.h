#pragma once

#include "Settlement.h"
#include<cstdlib>
#include<ctime>

class Game
{
private:
	bool isRunning;
	float deltaTime;
	int gameSpeed = 999;	//	Time in ms between loops

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

	//	Starts Game
	void Start();
	//	Stop Game
	void Stop() { isRunning = false; }
	
	Settlement* PlayerSett = new Settlement[1];
	int SettAmount = 0;
};


//	Random
static bool isFirstTimeSeed = true;

int RandomRange(int min, int max);
int ChooseRandom(int one, int two);
int ChooseRandom(int one, int two, int three);
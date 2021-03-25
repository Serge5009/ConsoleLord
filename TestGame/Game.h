#pragma once

#include<cstdlib>
#include<ctime>
#include "Player.h"

class Game
{
private:
	bool isRunning;
	bool isPlaying;	//	If false - freezes updates
	float deltaTime;
	int gameSpeed = 999;	//	Time in ms between loops

	int day;

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
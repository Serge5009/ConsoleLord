#pragma once

#include<cstdlib>
#include<ctime>
#include "Player.h"

class Game
{
private:
	bool isRunning;			//	Controls Game loop
	bool isPlaying;			//	If false - freezes updates
	short GameSpeed;		//	Game speed from 1 to 5
	float deltaTime;		//	Time in ms passed between loops
	int gameSpeed = 1000;	//	Freeze time in ms between loops

	int day;	//	Global day counter

	void GameLoop();		//	Main game loop

	void HandleEvents();	//	Handles input, called each loop

	void Update();			//	Handles all background actions that occure every day
							//	called only if isPlaying == true

	void Render();			//	Renders selected settlement or menu
			//	For now only outputs main player settlement

	void StartingScreen();	//	Outputs starting screen and handles input
	void HelpScreen();		//	Outputs help screen and waits for any key being pressed

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
	
	//	Total amount of settlements exsisting in the game
	int SettAmount = 0;
};


//	Random
static bool isFirstTimeSeed = true;

int RandomRange(int min, int max);
int ChooseRandom(int one, int two);
int ChooseRandom(int one, int two, int three);
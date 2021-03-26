#pragma once
#include "Settlement.h"

class Player
{
public:
		//	Constructor
	Player();
		//	Destructor
	~Player();

		
	void Update();	//	Handles all BG actions that haoppen to the player every day

	void RenderSett(short ID);	//	Renders settlement of given ID

	short SettAmount;
	Settlement* PlayerSett = new Settlement[1];
	int money;		//	Amount of money owned by the player

private:

};
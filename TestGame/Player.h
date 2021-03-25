#pragma once
#include "Settlement.h"

class Player
{
public:
	Player();
	~Player();

	void Update();
	void RenderSett(short ID);

	short SettAmount;
	Settlement* PlayerSett = new Settlement[1];
	int money;



private:

};


#include "Player.h"
#include "Settlement.h"
#include "Game.h"

Player::Player()
{
	//	PlayerSett array of 1 settlement is already created
	PlayerSett[0].ID = 0;	//	We adjust it's ID
	SettAmount = 1;			//	And sett amount of settlements owned by player

	money = RandomRange(100, 250);
}

Player::~Player()
{
	delete[] PlayerSett;	//	Deleting array of settlements
}

void Player::Update()	//	This functuion is  called every day if game is unpaused
{
	for (int i = 0; i < SettAmount; i++)
	{					//	Calls Update() for every owned settlement
		PlayerSett[i].Update();
	}


}

void Player::RenderSett(short ID)
{						//	Renders one settlement
	PlayerSett[ID].CoutSett();
}
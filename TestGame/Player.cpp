#include "Player.h"
#include "Settlement.h"

Player::Player()
{
	delete PlayerSett;
	PlayerSett = new Settlement[1];
	PlayerSett[0].ID = 0;
	SettAmount = 1;
	PlayerSett[0].CoutSett();
}

Player::~Player()
{

}

void Player::Update()
{
	for (int i = 0; i < SettAmount; i++)
	{
		PlayerSett[i].Update();
	}


}

void Player::RenderSett(short ID)
{
	PlayerSett[ID].CoutSett();
}

//delete[] PlayerSett;
#include "Settlement.h"
#include "Game.h"
#include "iostream"
#include <SDL.h>
#include <string>

using namespace std;

Settlement::Settlement()
{
	//	Identifying this settlement
	type = 0;	//	Village type !HARDCODED FOR NOW!
	daysExist = 0;
	//PopProgress = 0.0f;

	//	Creating enviroment
	enviromentType = RandomRange(0, ENVIROMENT_TYPES_TOTAL - 1);
	cout << "Creating enviroment, ID" << enviromentType << endl;
	GiveDefaultResources();
	DefaultResourcesMultiplier();
	DefaultResourcesDaily();

	GiveDefaultFood();
	foodDiversity = 3;
	DefaultFoodMultiplier();
	DefaultFoodDaily();

	AssignStartingStats();	//	Assigns settlement stats depending on its climate
							//	More at function definition
	void AvoidNegativeFood();
	void AvoidNegativeResources();



	//	Resources
	population = RandomRange(10, 25);
	freePop = population;
	money = RandomRange(0, 100);



	
}


//	This functions assigns starting resources and bonuses depending on 
//	enviroment type. Also assigns climate type.
//	It goes through all possible variants.
void Settlement::AssignStartingStats()
{
	switch (enviromentType)	//	UNFINISHED
	{
	case FOREST:
		climateType = RandomRange(VERY_COLD, NORMAL);
		//	Should add bigger chance for NORMAL later

		//	Forest is perfect for wood
		Resources[WOOD] += 20;
		Resources[WOOD] *= 2;	
		ResourcesDailyChange[WOOD] = 5;
		ResourcesMultiplier[WOOD] = 2.0f;

		//	And mushrooms
		Food[MUSHROOMS] += 10;
		FoodDailyChange[MUSHROOMS] = 3;
		FoodMultiplier[MUSHROOMS] = 1.5f;

		//	There are some wildfowl there
		Food[MEAT] += 20;
		FoodDailyChange[MEAT] = 5;
		FoodMultiplier[MEAT] = 1.5f;

		BuildCost = 1.5f;	//	Hard to build
		primaryFoodType = ChooseRandom(MEAT, MUSHROOMS);

		break;

	case PLAIN:
		climateType = RandomRange(VERY_COLD, HOT);
		
		//	It is a perfect place for WHEAT, BERRIES and VEGETABLES
		Food[BREAD] += 10;
		FoodMultiplier[BREAD] = 2.0f;
		Food[VEGETABLES] += 10;
		FoodMultiplier[VEGETABLES] = 1.5f;
		Food[BERRIES] += 10;
		FoodDailyChange[BERRIES] = 5;
		FoodMultiplier[BERRIES] = 2.0f;

		BuildCost = 0.5f;	//	Perfect for building
		primaryFoodType = ChooseRandom(BERRIES, BREAD);

		break;
	case STEPPE:
		climateType = RandomRange(COLD, NORMAL);
		// MUCH nigger chance of normal climat	// ADD LATER

		//	No wood in steppe((
		Resources[WOOD] -= 20;
		ResourcesMultiplier[WOOD] = 0.5f;

		//	Too dry for plants
		Food[BREAD] -= 10;
		FoodMultiplier[BREAD] = 0.8f;
		Food[VEGETABLES] -= 10;
		FoodMultiplier[VEGETABLES] = 0.8f;
		//	There are some berries
		Food[BERRIES] += 10;
		FoodMultiplier[BERRIES] = 1.3f;


		// Eat horses!!!
		Food[MEAT] += 10;
		FoodMultiplier[MEAT] = 1.5f;

		BuildCost = 0.5f;	//	Perfect for building
		primaryFoodType = ChooseRandom(MEAT, BERRIES);

		break;

	case RIVER_DELTA:
		climateType = RandomRange(COLD, HOT);
		
		//	Perfect for plants
		Food[BREAD] += 20;
		FoodMultiplier[BREAD] = 1.5f;
		Food[VEGETABLES] += 10;
		FoodMultiplier[VEGETABLES] = 1.3f;
		FoodMultiplier[FRUITS] = 1.3f;
		// And fishing
		Food[FISH] += 20;
		FoodDailyChange[FISH] = 5;
		FoodMultiplier[FISH] = 2.0f;
		//	Not that much stone & iron
		ResourcesMultiplier[STONE] = 0.7f;
		ResourcesMultiplier[IRON] = 0.8f;
		ResourcesMultiplier[CLAY] = 1.5f;

		BuildCost = 1.0f;	//	Normal cost
		primaryFoodType = ChooseRandom(FISH, BREAD);

		break;

	case RIVER_BANK:
		climateType = RandomRange(VERY_COLD, HOT);
		
		//	Perfect for plants
		Food[BREAD] += 20;
		FoodMultiplier[BREAD] = 1.7f;
		Food[VEGETABLES] += 10;
		FoodMultiplier[VEGETABLES] = 1.3f;
		// And fishing
		Food[FISH] += 30;
		FoodDailyChange[FISH] = 5;
		FoodMultiplier[FISH] = 2.0f;
		//	Not that much stone & iron
		ResourcesMultiplier[STONE] = 0.9f;
		ResourcesMultiplier[IRON] = 0.8f;
		ResourcesMultiplier[CLAY] = 1.3f;

		BuildCost = 0.9f;	//	Normal cost
		primaryFoodType = ChooseRandom(FISH, BREAD);

		break;

	case SEA_SHORE:
		climateType = RandomRange(NORMAL, HOT);

		//	Good for plants
		Food[BREAD] += 10;
		FoodMultiplier[BREAD] = 1.3f;
		Food[VEGETABLES] += 10;
		FoodMultiplier[VEGETABLES] = 1.3f;
		FoodMultiplier[FRUITS] = 1.3f;
		// And fishing
		Food[FISH] += 20;
		FoodDailyChange[FISH] = 5;
		FoodMultiplier[FISH] = 2.5f;
		//	Not that much stone & iron
		ResourcesMultiplier[STONE] = 0.8f;
		ResourcesMultiplier[IRON] = 0.8f;

		BuildCost = 1.0f;	//	Normal cost
		primaryFoodType = ChooseRandom(FISH, BREAD);

		break;

	case DESERT_OASIS:
		climateType = RandomRange(HOT, VERY_HOT);
		
		// No fish
		Food[FISH] -= 20;
		FoodMultiplier[FISH] = 0.5f;

		// No wood
		Resources[WOOD] -= 20;
		ResourcesMultiplier[WOOD] = 0.5f;
		ResourcesMultiplier[CLAY] = 0.8f;

		//	Go eat fruits!
		Food[FRUITS] += 20;
		FoodDailyChange[FRUITS] = 5;
		FoodMultiplier[FRUITS] = 1.5f;

		BuildCost = 0.8f;	//	Normal cost
		primaryFoodType = FRUITS;

		break;

	case HILLS:
		climateType = RandomRange(COLD, HOT);

		// No fish
		Food[FISH] -= 10;
		FoodMultiplier[FISH] = 0.8f;

		// Some wood
		Resources[WOOD] += 20;
		ResourcesMultiplier[WOOD] = 1.5f;
		//	And stone
		Resources[STONE] += 20;
		ResourcesMultiplier[STONE] = 1.5f;

		//	Not the biggest food variety
		Food[BREAD] += 10;
		FoodMultiplier[BREAD] = 1.1f;
		Food[BERRIES] += 15;
		FoodMultiplier[BERRIES] = 1.5f;

		BuildCost = 1.2f;	//	Higher cost
		primaryFoodType = ChooseRandom(BERRIES, BREAD);

		break;

	case MOUNTAINE:
		climateType = RandomRange(VERY_COLD, NORMAL);
		// No fish
		Food[FISH] -= 50;
		FoodMultiplier[FISH] = 0.3f;

		// Some wood
		Resources[WOOD] += 10;
		ResourcesMultiplier[WOOD] = 1.3f;
		//	And stone
		Resources[STONE] += 50;
		ResourcesMultiplier[STONE] = 2.5f;
		Resources[IRON] += 30;
		ResourcesMultiplier[IRON] = 2.0f;

		//	WHERE FOOD?!
		Food[BREAD] -= 20;
		FoodMultiplier[BREAD] = 0.8f;
		Food[BERRIES] -= 10;
		FoodMultiplier[BERRIES] = 0.9f;

		BuildCost = 1.5f;	//	Higher cost
		primaryFoodType = ChooseRandom(BERRIES, BREAD);

		break;

		break;


	default:	//	Should not be activated
		GiveDefaultResources();
		climateType = NORMAL;

		//	Debug
		cout << "No enviroment with ID " << enviromentType << " found!!!" << endl;
		cout << "Setting all settlement " << ID << " to defaults" << endl;
		SDL_Delay(10000);	//	Freeze for 10 sec
		break;
	}


}

//	This function assigns random resources amount for everything
void Settlement::GiveDefaultResources()
{
	for (int i = 0; i < RESOURCES_TYPES_TOTAL; i++)
	{	//	Randomly assigns resources amount
		Resources[i] = RandomRange(10, 50);
	}
}

//	Just checks for negatives and assigns 0
void Settlement::AvoidNegativeResources()
{
	for (int i = 0; i < RESOURCES_TYPES_TOTAL; i++)
	{
		if (Resources[i] < 0)
			Resources[i] = 0;
	}
}
//	Sets all resources mult to 1.0
void Settlement::DefaultResourcesMultiplier()
{
	for (int i = 0; i < RESOURCES_TYPES_TOTAL; i++)
	{
		ResourcesMultiplier[i] = 1.0;
	}
}
//	Sets all resources daily change to 0
void Settlement::DefaultResourcesDaily()
{
	for (int i = 0; i < RESOURCES_TYPES_TOTAL; i++)
	{
		ResourcesDailyChange[i] = 0;
	}
} 


void Settlement::GiveDefaultFood()
{
	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)
	{	//	Randomly assigns resources amount
		Food[i] = RandomRange(10, 50);
	}
	primaryFoodType = BREAD;
}

//	Just checks for negatives and assigns 0
void Settlement::AvoidNegativeFood()
{
	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)
	{
		if (Food[i] < 0)
			Food[i] = 0;
	}
}
//	Sets all food mult to 1.0
void Settlement::DefaultFoodMultiplier()
{
	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)
	{
		FoodMultiplier[i] = 1.0;
	}
}
//	Sets all food daily change to 0
void Settlement::DefaultFoodDaily()
{
	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)
	{
		FoodDailyChange[i] = 0;
	}
}

//	Sums up all food types
int Settlement::CalculateFood()
{
	int foodSum = 0;
	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)
	{
		foodSum += Food[i];
	}
	return foodSum;
}

//	Allows people to eat different types of food
//	Also defines food diversity
int Settlement::EatFood(int amount)
{
	if (food < amount)
	{isStarving = true;}
	else
	{isStarving = false;}
	int eaten = 0;	//	How much food was already eaten
	int portion = amount / FOOD_TYPES_TOTAL;	//	Size of one portion of a food type
	short types = 0;	//	Food variety
	
	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	Loops through all food types;
	{	//	This is the first loop through all food types; it allows to apply variety bonus
		if (Food[i] >= portion)
		{
			Food[i] -= portion;
			eaten += portion;
			//if (isFirstTimeEaten[i])
			types++;
			//isFirstTimeEaten[i] = false;
		}
	}	//	If all types of food are available, next loop will not be activated

	int loops = 0;
	while (amount > eaten && loops < 100)
	{	//	This loop allows to eat existing food insted of missed one
		loops++;	//	this should save us from stucking in this loop
		portion = (amount - eaten) / FOOD_TYPES_TOTAL;	// new portion size
		if (portion < 1)	//	Minimal portion size is 1
			portion = 1;	//	to avoid endless loops

		for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	Loops through all food types;
		{
			if (Food[i] >= portion)
			{
				Food[i] -= portion;
				eaten += portion;
			}
		}
	}
	return types;
}

void Settlement::GrowPop()
{/*
	if (isStarving)
	{
		PopProgress -= (float)population / 20;
	}
	else if (food > population * 5)
	{
		float eaten = (float)food - (float)population * 4.5;
		PopProgress += eaten / 100;
		food -= (int)eaten;
	}
	else
	{
		PopProgress += (float)population / 1000;
	}
*/
}


//	All changes occuring every game loop (day)
void Settlement::Update()
{
	daysExist++;	//	Another day...

	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	Adds food
	{Food[i] += FoodDailyChange[i] * FoodMultiplier[i];}
	Food[primaryFoodType] += (freePop / 2) * FoodMultiplier[primaryFoodType];	//	Adds primary food

	for (int i = 0; i < RESOURCES_TYPES_TOTAL; i++)	//	Adds resources
	{Resources[i] += ResourcesDailyChange[i] * ResourcesMultiplier[i];}

	food = CalculateFood();
	foodDiversity = EatFood(population);	//	People need food


	if (isStarving)	//	people can die from starvation
		population -= population / 20 + 1;
}

void Settlement::CoutSett()
{
	system("CLS");
	cout << "Settlement ID: " << ID << "\t Exists for: " << daysExist << " days" << endl;
	cout << "Population: " << population << "\tMoney: " << money << endl;
	cout << "Food: " << CalculateFood();
		if (isStarving)
			{cout << "\t\tSettlement is starving!!!";}
		cout << endl;
	cout << Food[BREAD] << " BRD\t" << Food[FISH] << " FSH\t" << Food[BERRIES] << " BER\t" << Food[MEAT] << " MEA" << endl;
	cout << Food[MUSHROOMS] << " MRM\t" << Food[VEGETABLES] << " VEG\t" << Food[FRUITS] << " FRT\t" << endl;
	cout << "There are " << foodDiversity << " types of food available" << endl;
	//cout << "Population progress: " << PopProgress << endl;
	cout << "Resources" << endl;
	cout << Resources[WOOD] << " WOD \t" << Resources[STONE] << " STN \t" << Resources[IRON] << " IRN" << endl;
	cout << Resources[STEEL] << " STL \t" << Resources[CLAY] << " CLY" << endl;

	cout << "Climate is ";
	switch (climateType)
	{
	case VERY_COLD:
		cout << "very cold!";
		break;
	case COLD:
		cout << "cold.";
		break;
	case NORMAL:
		cout << "perfect!";
		break;
	case HOT:
		cout << "hot.";
		break;
	case VERY_HOT:
		cout << "very hot!";
		break;
	default:	//	Debug
		cout << "Error! ID" << climateType << " is not found!";
		break;
	}
	cout << "\t\tLocation: ";
	switch (enviromentType)
	{
	case FOREST:
		cout << "Forest";
		break;
	case PLAIN:
		cout << "Plains";
		break;
	case STEPPE:
		cout << "Steppe";
		break;
	case RIVER_DELTA:
		cout << "River deltha";
		break;
	case RIVER_BANK:
		cout << "River bank";
		break;
	case SEA_SHORE:
		cout << "Sea shore";
		break;
	case DESERT_OASIS:
		cout << "Oasis";
		break;
	case HILLS:
		cout << "Hills";
		break;
	case MOUNTAINE:
		cout << "Mountaine";
		break;
	default:	//	Debug
		cout << "Error! ID" << enviromentType << " is not found!";
		break;
	}
	cout << endl;

	cout << endl;


	//SDL_Delay(2000);
}
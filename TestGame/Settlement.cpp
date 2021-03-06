#include "Settlement.h"
#include "Game.h"
#include "iostream"
#include <SDL.h>
#include <string>

using namespace std;

short Settlement::SettNum = 0;	//	Total amount of Settlements exsisting in the game

	//	Constructor
Settlement::Settlement()
{
		//	Identifying this settlement:
	type = 0;			//	Village type !HARDCODED FOR NOW!
	GlobalID = SettNum;	
	SettNum++;		//	Adding one to settlement counter
		
		//	Settihg defaults:
	daysExist = 0;		
	PopProgress = 0.0f;	
	population = RandomRange(10, 25);	//	Random population
	requiredPop = 0;
	foodDiversity = 0;
	freePop = population;

	money = RandomRange(0, 100);

	GiveDefaultResources();			
	DefaultResourcesMultiplier();
	DefaultResourcesDaily();
	GiveDefaultFood();
	DefaultFoodMultiplier();
	DefaultFoodDaily();

		//	Creating enviroment:
	enviromentType = RandomRange(0, ENVIROMENT_TYPES_TOTAL - 1);	//	One of exsisting enviroment types

	AssignEnviromentStats();//	Assigns settlement stats and cliamte depending on its enviroment
							//	More at function definition

	AssignClimateStats();	//	Assign settlement stats depending on its climate

	AvoidNegativeFood();		//	Checking for negatives
	AvoidNegativeResources();	

	//	Here will be code that creates 1-3 buildings
}

	//	Destructor
Settlement::~Settlement()
{

}

//	This functions assigns starting resources and bonuses depending on 
//	enviroment type. Also assigns climate type.
//	It goes through all possible variants.
void Settlement::AssignEnviromentStats()
{
	switch (enviromentType)
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
		primaryFoodType = ChooseRandom(BERRIES, BREAD, BERRIES);

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
		FoodDailyChange[BERRIES] = 3;
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
		FoodDailyChange[BERRIES] = 5;
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
		FoodMultiplier[BERRIES] = 0.9f;
		FoodDailyChange[BERRIES] = 3;	//	Go find something to eat!!
		FoodDailyChange[MEAT] = 3;

		BuildCost = 1.5f;	//	Higher cost
		primaryFoodType = ChooseRandom(BERRIES, MEAT);

		break;

		break;


	default:	//	Should not be activated
		GiveDefaultResources();
		DefaultResourcesMultiplier();
		DefaultResourcesDaily();
		DefaultFoodMultiplier();
		DefaultFoodDaily();
		GiveDefaultFood();
		
		climateType = NORMAL;

		//	Debug
		cout << "No enviroment with ID " << enviromentType << " found!!!" << endl;
		cout << "Setting all settlement " << ID << " to defaults" << endl;
		SDL_Delay(10000);	//	Freeze for 10 sec
		break;
	}


}

//	Adds or removes stats depending on climate type
//	called right after AssignEnviromentStats() so climate type is already known
void Settlement::AssignClimateStats()
{
	switch (climateType)
	{
	case VERY_COLD:
		money += 100;	//	Bonus
		for(int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	No food where it's cold
		{FoodMultiplier[i] -= 0.2f;}
		FoodMultiplier[FISH] += 0.5f;	//	Fishing and hunting is the only way to survive
		FoodMultiplier[MEAT] += 0.5f;

		ResourcesDailyChange[WOOD] -= 10;	//	You need some wood to make fire
		ResourcesMultiplier[WOOD] += 0.5f;	//	So people collect more of it

		break;

	case COLD:
		money += 50;	//	Bonus
		for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	No food where it's cold
		{FoodMultiplier[i] -= 0.1f;}
		FoodMultiplier[FRUITS] -= 0.5f;
		FoodMultiplier[FISH] += 0.3f;	//	Fishing and hunting is the only way to survive
		FoodMultiplier[MEAT] += 0.3f;
		FoodMultiplier[MUSHROOMS] += 0.5f;
		Food[MUSHROOMS] += 50;	//	Yay! Mushroom time!



		ResourcesDailyChange[WOOD] -= 5;	//	You need some wood to make fire
		ResourcesMultiplier[WOOD] += 0.3f;	//	So people collect more of it

		break;

	case NORMAL:
		FoodMultiplier[BREAD] += 0.5f;
		FoodMultiplier[VEGETABLES] += 0.3f;
		FoodMultiplier[BERRIES] += 0.5f;

		BuildCost -= 0.1f;

		break;

	case HOT:
		money += 50;	//	Bonus
		for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	No food where it's hot
		{FoodMultiplier[i] -= 0.1f;}
		FoodMultiplier[MUSHROOMS] -= 0.5f;
		FoodMultiplier[FISH] -= 0.3f;
		FoodMultiplier[VEGETABLES] -= 0.2f;

		FoodMultiplier[FRUITS] += 0.5f;
		FoodDailyChange[FRUITS] += 5;

		ResourcesMultiplier[WOOD] -= 0.3f;

		break;

	case VERY_HOT:
		money += 100;	//	Bonus
		for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	No food where it's hot
		{
			FoodMultiplier[i] -= 0.2f;
		}
		FoodMultiplier[MUSHROOMS] -= 0.5f;

		FoodMultiplier[FRUITS] += 0.5f;
		FoodDailyChange[FRUITS] += 5;

		ResourcesMultiplier[WOOD] -= 0.5f;

		break;

	default:
		//	Debug
		cout << "No climate with ID " << climateType << " found!!!" << endl;
		cout << "Setting all settlement " << ID << " to defaults" << endl;
		SDL_Delay(10000);	//	Freeze for 10 sec
		break;
	}
}

//	This function assigns random resources amount for all types
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
		{
			Resources[i] = 0;
		}
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
//	This function assigns random food amount for all types
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
		{
			Food[i] = 0;
		}
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
	{	//	loops through all types
		foodSum += Food[i];
	}
	return foodSum;
}

//	Allows people to eat different types of food
//	returns food diversity
int Settlement::EatFood(int amount)
{
	if (food < amount)		//	Checking is there enough food
	{isStarving = true;}
	else
	{isStarving = false;}

	//	We will loop throug all food types once and (if possible) take some amount of each type
	//	Each successfuly eaten portion of food adds 1 to available types (returned value)
	//	and adds amount of eaten food to "eaten" variable
	//	Than we will make the same loop (but without increasing food variety) until "eaten" will
	//	reach amount of food needed to be eaten
	
	int eaten = 0;				//	How much food was already eaten
	int portion = amount / FOOD_TYPES_TOTAL;	//	Size of one portion of a food type
	short types = 0;			//	Food variety (this value will be returned)
	
	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	Loops through all food types;
	{	//	This is the first loop through all food types; it allows to apply variety bonus
		if (Food[i] >= portion)
		{		//	Takes portion of food if can to do it
			Food[i] -= portion;
			eaten += portion;	//	Adds to eaten
			types++;			//	Adds one more type
		}
	}	//	If all types of food are available, next loop will not be activated

	int loops = 0;	//	Should save us from endless loop
	while (amount > eaten && loops < 100)
	{	//	This loop allows to eat existing food insted of missed one
		loops++;
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
		//	DEBUG
		if (loops == 99)
		{cout << "DEBUG! EatFood() loop reached 99!\nshould not appear" << endl; SDL_Delay(1000);}
	}
	AvoidNegativeFood();
	return types;
}

//	Handles growth and decline of population
void Settlement::GrowPop()
{		//	New function needed
	if (isStarving)
	{
		PopProgress -= (float)population / 20;
	}	
	else if (food > population * 10)
	{
		float eaten = (float)food - (float)population * 9.5;
		PopProgress += eaten / 100;
		EatFood((int)eaten);
	}
	else
	{
		PopProgress += (float)population / 1000;
	}

	if (PopProgress >= 1 || PopProgress <= -1)
	{
		if (PopProgress <= -1)
			Food[MEAT] += (int)PopProgress * 5;
		population += (int)PopProgress;
		PopProgress -= (int)PopProgress;
		// ???
	}
}

//	All changes that happen every game loop (day)
void Settlement::Update()
{
	daysExist++;	//	Another day...

	for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	Adds food of each type
	{Food[i] += FoodDailyChange[i] * FoodMultiplier[i];}
	Food[primaryFoodType] += (freePop / 2) * FoodMultiplier[primaryFoodType];	//	Adds primary food

	for (int i = 0; i < RESOURCES_TYPES_TOTAL; i++)	//	Adds resources of each type
	{Resources[i] += ResourcesDailyChange[i] * ResourcesMultiplier[i];}

	food = CalculateFood();			//	Sums up all food
	foodDiversity = EatFood(population);	//	People need food

	GrowPop();	//	Changes value of PopProgress depending on food of available
	freePop = CalculateFreePop();	//	Calculetes amount of idle population
}

	//	Outputs settlement stats to console
void Settlement::CoutSett()
{	//	New function needed
	cout << name << " has ID: " << ID << "\t And exists for: " << daysExist << " days" << endl;
	cout << "Population: " << population << "\tFree " << freePop << endl;
	cout << "Food: " << CalculateFood();
		if (isStarving)
			{cout << "\t\tSettlement is starving!!!";}
		else 
			{cout << "\t\tPrimary food type is " << foodNames[primaryFoodType];}
		cout << endl;

		for (int i = 0; i < FOOD_TYPES_TOTAL; i++)	//	Looping throug all resources types
		{
			if (i == FOOD_TYPES_TOTAL / 2)
				cout << endl;	//	Deviding resources for 2 lines

			cout << Food[i] << " " << foodNames[i] << "\t";	//	Outputs amount and name of resource

		}		cout << endl;	//	endl after all resources are outputed

	cout << "There are " << foodDiversity << " types of food available" << endl;
	cout << "Population progress: " << PopProgress << endl << endl;
	cout << "Resources" << endl;
	for (int i = 0; i < RESOURCES_TYPES_TOTAL; i++)	//	Looping throug all resources types
	{
		if (i == RESOURCES_TYPES_TOTAL / 2)
			cout << endl;	//	Deviding resources for 2 lines

		cout << Resources[i] << " " << resourcesNames[i] << "\t";	//	Outputs amount and name of resource
		
	}		cout << endl << endl;	//	endl after all resources are outputed


	cout << "Climate is " << climateNames[climateType];	
	
	cout << "\t\tLocation: ";	//	Switch will be changed to string array in future
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
}
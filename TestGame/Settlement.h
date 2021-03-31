#pragma once
#include <string>

//		To do:
//	Arrays of names for resources and cimate type
//	Make new EatFood() function
//	Make new starvation & population system
//	More resources & food
//	AI


//	Enums for extandable arrays of resources, food & climate
enum RESOURCES
{
	WOOD, STONE, IRON, STEEL, COAL, CLAY, FUR, WOOL,

	RESOURCES_TYPES_TOTAL
};
const char resourcesNames[RESOURCES_TYPES_TOTAL][8] = { 
	"Wood  ", "Stone ", "Iron  ", "Stell ", "Coal  ", "Clay  ", "Fur   ", "Wool  " };	//	All names are same size (I use spaces to make them equal)

enum FOOD
{
	BREAD, VEGETABLES, FRUITS, BERRIES, MUSHROOMS, FISH, MEAT, DAIRY,

	FOOD_TYPES_TOTAL
};
const char foodNames[FOOD_TYPES_TOTAL][16] = { 
	"Bread    ", "Vegetable", "Fruits   ", "Berries  ", "Mushrooms", "Fish     ", "Meat     ", "Dairy    " };	//	All names are same size (I use spaces to make them equal)


enum CLIMATE_TYPE
{
	VERY_COLD, COLD, NORMAL, HOT, VERY_HOT,

	CLIMATE_TYPES_TOTAL
};
const char climateNames[CLIMATE_TYPES_TOTAL][32] = {
	"\033[34mVery cold\033[37m", "\033[36mCold     \033[37m", "\033[32mPerfect  \033[37m", "\033[33mHot      \033[37m", "\033[31mVery hot \033[37m"};	//	All names are same size (I use spaces to make them equal)


enum ENVIROMENT_TYPE
{
	FOREST, PLAIN, STEPPE, RIVER_DELTA, RIVER_BANK, SEA_SHORE, DESERT_OASIS, 
	HILLS, MOUNTAINE,

	ENVIROMENT_TYPES_TOTAL
};


class Settlement
{
private:
	short enviromentType;	//	Where city is situated (forest, plain, river...)
	short climateType;		//	Climate in that location (cold, normal, hot...)

	void AssignEnviromentStats();	//	Changes settlement resources, multiliers and climate
									//	depending on enviroment
	void AssignClimateStats();		//	Chenges resources, multipliers and icomes based on climate type

	char name[32] = "Cornwall";	//	City name	// HADCODED for now

	int daysExist;	//	How old is this city (in days)
	

		//				//
		//	RESOURCES	//
		//				//

	int money;	//	Can be spent on some buildings, perks. Payed as tax to owner
				//	needed to trade with other settlements

	int Resources[RESOURCES_TYPES_TOTAL];				//	Array with all resources types

	int ResourcesDailyChange[RESOURCES_TYPES_TOTAL];	//	Daily income of resources

	float ResourcesMultiplier[RESOURCES_TYPES_TOTAL];	//	Any resource income is multiplied
														//	by this float (normal is 1.0f)

	float BuildCost;		//	All buildings costs are multiplied by this float

	void GiveDefaultResources();		//	Gives random amount of all resources (10 - 50)
	void DefaultResourcesDaily();		//	Sets all daily resources income to 0
	void DefaultResourcesMultiplier();	//	Sets all resource mutl. to 1.0f
	void AvoidNegativeResources();		//	Checks all resources for negatives (if neg. assigns 0)


		//			//
		//	Food	//
		//			//

	int food;			//	Sum of all types of food
	int Food[FOOD_TYPES_TOTAL];				//	Array with all food types

	int FoodDailyChange[FOOD_TYPES_TOTAL];	//	Daily food income

	int FoodMultiplier[FOOD_TYPES_TOTAL];	//	Any food income is multiplied
											//	by this float (normal is 1.0f)

	short primaryFoodType;	//	Depends on enviroment. It's a food type collected by idle people

	void GiveDefaultFood();			//	Gives random amount of all food (10 - 50)
	void DefaultFoodDaily();		//	Sets all daily food income to 0
	void DefaultFoodMultiplier();	//	Sets all food mutl. to 1.0f
	void AvoidNegativeFood();		//	Checks all food for negatives (if neg. assigns 0)
	

	//string FoodName[FOOD_TYPES_TOTAL] = { "Bread", "Fish", "Berries", "Mushrooms", "Vegetables", "Fruits", "Meat" };
	
	int CalculateFood();	//	Sums all food types

	int EatFood(int amount);	//	Takes some amount of each type of food until it reaches passed value
	bool isStarving;	//	true if there was not enough food in EatFood()
	int foodDiversity;	//	Number of food types that were available to eat last day


	//				//
	//	Population	//
	//				//

	int population;		//	Total number of people living in this city
	int freePop;		//	Idle people, who harvest food of primary type
	int requiredPop;	//	Total number of people working in buildings

	float PopProgress;	//	Progress of population growth/decline
						//	every 1.0 of PopProgress is changed for 1 population
						//	same for negatives
	
	void GrowPop();		//	Changes value of PopProgress depending on food of settlement

						//	Returns amount of free population
	int CalculateFreePop() {return population - requiredPop;}
	
	
public:
	
	
	short ID;				//	ID of settlement for Player
	short GlobalID;			//	Global ID of settlement
	static short SettNum;	//	Total amount of Settlements exsisting in the game
	short type;				//	Type (village/town...)


	Settlement();	//	Constructor
	~Settlement();	//	Destructor

	void Update();	//	Handles all backround game actions of this settlement
	void CoutSett();	//	Outputs info about settlement to the console

	
};
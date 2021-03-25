#pragma once
#include <string>

//	String enums?

enum RESOURCES
{
	WOOD, STONE, IRON, STEEL, CLAY,

	RESOURCES_TYPES_TOTAL
};

enum FOOD
{
	BREAD, FISH, BERRIES, MUSHROOMS, VEGETABLES, FRUITS, MEAT,

	FOOD_TYPES_TOTAL
};

enum CLIMATE_TYPE
{
	VERY_COLD, COLD, NORMAL, HOT, VERY_HOT,

	CLIMATE_TYPES_TOTAL
};

enum ENVIROMENT_TYPE
{
	FOREST, PLAIN, STEPPE, RIVER_DELTA, RIVER_BANK, SEA_SHORE, DESERT_OASIS, 
	HILLS, MOUNTAINE,

	ENVIROMENT_TYPES_TOTAL
};


class Settlement
{
private:
	short climateType;
	short enviromentType;

	int daysExist;

		//	Resources
	int population, money;

	int Resources[RESOURCES_TYPES_TOTAL];	//	Array with all resources types
	void GiveDefaultResources();
	void AvoidNegativeResources();
	float ResourcesMultiplier[RESOURCES_TYPES_TOTAL];
	float BuildCost;
	void DefaultResourcesMultiplier();
	int ResourcesDailyChange[RESOURCES_TYPES_TOTAL];
	void DefaultResourcesDaily();

		//	Food
	int food;	//	Total amount of food
	int CalculateFood();	//	Sums all food types
	bool isStarving;

	int foodDiversity;
	int EatFood(int amount);

	int Food[FOOD_TYPES_TOTAL];	//	Array with all food types
		void GiveDefaultFood();
		void AvoidNegativeFood();
	int FoodMultiplier[FOOD_TYPES_TOTAL];
	//string FoodName[FOOD_TYPES_TOTAL] = { "Bread", "Fish", "Berries", "Mushrooms", "Vegetables", "Fruits", "Meat" };
		void DefaultFoodMultiplier();
	int FoodDailyChange[FOOD_TYPES_TOTAL];
		void DefaultFoodDaily();
	short primaryFoodType;	//	Depends on enviroment. It's a food type collected by idle people

		void GrowPop();
	float PopProgress;	//	Progress of population growth/decline
	int freePop;
	int requiredPop;
		int CalculateFreePop();
		 
		void AssignEnviromentStats();
		void AssignClimateStats();
	
		char name[32] = "Cornwall";

public:
	
	short ID;
	short GlobalID;
	short type;


	Settlement();
	void Update();
	void CoutSett();

	static int SettNum;
};


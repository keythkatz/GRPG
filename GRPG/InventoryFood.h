#ifndef _INVENTORY_FOOD_H                 // Prevent multiple definitions if this 
#define _INVENTORY_FOOD_H                 // file is included in more than one place

#include "constants.h"
#include "InventoryItem.h"

class InventoryFood : public InventoryItem
{
private:
	int foodState;
public:
	// constructor
	InventoryFood():InventoryItem(){}//If you don't have a .cpp, don't put ';', put '{}'
	InventoryFood(Item* item, int csc,int state)
		:InventoryItem(item, csc)
	{
		foodState = state;
	}
	int getFoodState(){ return foodState; }
	int setFoodState(int i){ foodState = i; }

	virtual InventoryFood* clone() {
		return new InventoryFood(*this);
	}
};
#endif
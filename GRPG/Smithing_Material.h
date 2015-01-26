#ifndef _SMITHING_MATERIAL_H			         // Prevent multiple definitions if this 
#define _SMITHING_MATERIAL_H		             // file is included in more than one place

#include "item.h"

class Smithing_Material : public Item
{
private:
	float strMultiplier;
	float defMultiplier;
public:
	Smithing_Material(){ Item(); }
	Smithing_Material(string n, string d, string i, int m, int c, float s, float de){
		Item(n, d, i, m, c);
		strMultiplier = s;
		defMultiplier = de;
	}
	float getStrMultiplier() { return strMultiplier; }
	void setStrMultiplier(float i){ strMultiplier = i; }
	float getDefMultiplier() { return defMultiplier; }
	void setDefMultiplier(float i){ defMultiplier = i; }
};
#endif
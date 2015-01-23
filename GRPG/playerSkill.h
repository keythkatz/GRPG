#ifndef _PLAYER_SKILL_H                 // Prevent multiple definitions if this 
#define _PLAYER_SKILL_H                 // file is included in more than one place

#include "constants.h"
#include <string>
#include <vector>

class PlayerSkill
{
private:
	//Attributes of a Skill
	//std::string name;//name of skill
	//std::string description;//description of skill
	//int exp_gain;//skill gain per action done

	long experience;//amt of experience
public:
	// constructor
	PlayerSkill();

	int getSkillLevel();


	// inherited member functions
	void gainXP(long xp);
};
#endif
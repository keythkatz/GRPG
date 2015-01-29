#include "PersonLoader.h"
#include "Enemy.h"
#include "NPC.h"

void PersonLoader::loadAllNPCs()
{
	ifstream characterstream;
	//Friendly Characters
	characterstream.open(friendlynpcDataLocation);
	if (characterstream.is_open()){
		string name, img_filename, description;
		int id, cols;
		float movementspd, attackcd, height, width, colHeight, colWidth;
		while (!characterstream.eof()){
			characterstream >> id >> name >> img_filename >> movementspd >> attackcd >> height >> width >> cols >> colHeight >> colWidth >> description;
			NPC myChar = NPC(img_filename, movementspd, attackcd, height, width, cols, colHeight, colWidth, name, description, 9999, false);//almost infinite health
			map_npcs[id] = myChar;
		}
		characterstream.close();
	}
	//All Enemies
	characterstream.open(enemyDataLocation);
	if (characterstream.is_open()){
		string name, img_filename, description;
		int id, atk, str, def, hp, cols;
		float movementspd, attackcd, dmg_red, width, height, colHeight, colWidth;
		while (!characterstream.eof()){
			characterstream >> id >> name >> img_filename >> movementspd >> attackcd>> height >> width >> cols >> colHeight >> colWidth
				>>  description >> atk >> str >> def >> hp >> dmg_red;
			Enemy myChar = Enemy(img_filename, movementspd, attackcd, height, width, cols, colHeight, colWidth, name, description, hp, atk, str, def, dmg_red);
			map_npcs[id] = myChar;
		}
		characterstream.close();
	}
}
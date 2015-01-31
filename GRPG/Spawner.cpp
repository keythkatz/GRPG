#include "Spawner.h"
#include "NPC.h"
#include "PersonLoader.h"
#include <sstream>

Spawner::Spawner(Game* gp, int spawn, int cd, Entity* v) : Tile(){
	gamePtr = gp;
	npcId = spawn;
	cooldown = cd;
	victim = v;
	timeOfDeath.QuadPart = 0;
	Tile(false);
}

void Spawner::spawn(){
	stringstream ss;
	ss << getX() << "," << getY();
	spawnedNPC = NPC::spawn(gamePtr, npcId, VECTOR2(x, y), victim);
	gamePtr->addSpawnLink(ss.str(), spawnedNPC);
	timeOfDeath.QuadPart = 0; // 0 = no death
}

void Spawner::update(){
	stringstream ss;
	ss << getX() << "," << getY();
	if (gamePtr->getSpawnLink(ss.str()) == NULL && timeOfDeath.QuadPart == 0){ // If dead and not recorded dead yet
		QueryPerformanceCounter(&timeOfDeath); // Record time of death
	}

	if (timeOfDeath.QuadPart != 0){
		LARGE_INTEGER currTime, timerFreq;
		float timeSinceLastSpawn;
		QueryPerformanceCounter(&currTime);
		QueryPerformanceFrequency(&timerFreq);
		timeSinceLastSpawn = (float)(currTime.QuadPart - timeOfDeath.QuadPart) / (float)timerFreq.QuadPart;

		if (timeSinceLastSpawn > cooldown){
			spawn();
		}
	}
}

// Can't do respawning yet because NPC can't die yet
#pragma once

#include <Core/GPU/Mesh.h>

#include "Block.h"
#include <map>

using namespace std;

class Bird
{
public:
	Bird();
	~Bird();

	void jump();
	void update(float deltaTime);
	bool collides(Block * block);

	map<string, pair<Mesh*, glm::mat3>> getMeshInfo();
private:
	float x, y;
	float speed;
	float rotation;
	float radius;
	float boundingCircleX, boundingCircleY;

	map<string, pair<Mesh*, glm::mat3>> meshInfo;
	Mesh * body, *head, *beak;
};
#pragma once

#include <Core/GPU/Mesh.h>
#include <utility>

using namespace std;

class Block
{
public:
	Block();
	~Block();

	void update(float deltaTime);
	void setSize(float width, float height);
	void setPosition(float x, float y);
	glm::vec2 getPosition();
	glm::vec2 getSize();
	
	pair<Mesh*, glm::mat3> getMeshInfo();

private:
	float x, y;
	float scaleX, scaleY;

	Mesh * mesh;
	glm::mat3 modelMatrix;
};
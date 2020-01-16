#include "Block.h"

#include "Transform2D.h"

#include <vector>

using namespace std;

Block::Block()
{
	mesh = new Mesh("block");

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)),
		VertexFormat(glm::vec3(0, 100, 0), glm::vec3(0, 1, 0)),
		VertexFormat(glm::vec3(100, 100, 0), glm::vec3(0, 1, 0)),
		VertexFormat(glm::vec3(100, 0, 0), glm::vec3(0, 1, 0))
	};

	vector<unsigned short> indices
	{
		0, 1, 2,
		2, 0, 3
	};

	mesh->InitFromData(vertices, indices);
	modelMatrix = glm::mat3(1);

	x = y = 0;
}

Block::~Block()
{
	if (mesh != nullptr)
	{
		delete mesh;
	}
	mesh = nullptr;
}

void Block::update(float deltaTime)
{
	x -= 100 * deltaTime;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(x, y);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
}

void Block::setSize(float width, float height)
{
	scaleX = width / 100.f;
	scaleY = height / 100.f;
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
}

void Block::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	modelMatrix *= Transform2D::Translate(x, y);
}

glm::vec2 Block::getPosition()
{
	return glm::vec2(x, y);
}

glm::vec2 Block::getSize()
{
	return glm::vec2(100 * scaleX, 100 * scaleY);
}

pair<Mesh*, glm::mat3> Block::getMeshInfo()
{
	return pair<Mesh*, glm::mat3>(mesh, modelMatrix);
}

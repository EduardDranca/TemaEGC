#include "Bird.h"
#include "Transform2D.h"
#include <iostream>

using namespace std;

Bird::Bird()
{
	body = new Mesh("body");
	head = new Mesh("head");
	beak = new Mesh("beak");

	x = 50;
	y = 300;
	speed = 0;
	rotation = 0;
	radius = 20;
	boundingCircleX = 80;
	boundingCircleY = 315;

	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0.2f, 0.3f)),
			VertexFormat(glm::vec3(0, 30, 0), glm::vec3(0, 0.2f, 0.3f)),
			VertexFormat(glm::vec3(30, 30, 0), glm::vec3(0, 0.2f, 0.3f)),
			VertexFormat(glm::vec3(30, 0, 0), glm::vec3(0, 0.2f, 0.3f))
		};

		vector<unsigned short> indices
		{
			0, 1, 2,
			2, 0, 3
		};

		body->InitFromData(vertices, indices);
		glm::mat3 modelMatrix = glm::mat3(1);

		modelMatrix *= Transform2D::Translate(50, 300);

		meshInfo["body"] = pair<Mesh*, glm::mat3>(body, modelMatrix);
	}

	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0.14f, 0.08f)),
			VertexFormat(glm::vec3(0, 24, 0), glm::vec3(1, 0.14f, 0.08f)),
			VertexFormat(glm::vec3(15, 18, 0), glm::vec3(1, 0.14f, 0.08f)),
			VertexFormat(glm::vec3(15, 6, 0), glm::vec3(1, 0.14f, 0.08f))
		};

		vector<unsigned short> indices
		{
			0, 1, 2,
			2, 0, 3
		};

		head->InitFromData(vertices, indices);

		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(80, 303);

		meshInfo["head"] = pair<Mesh*, glm::mat3>(head, modelMatrix);
	}

	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0.63f, 0.08f)),
			VertexFormat(glm::vec3(0, 9, 0), glm::vec3(1, 0.63f, 0.08f)),
			VertexFormat(glm::vec3(15, 4.5, 0), glm::vec3(1, 0.63f, 0.08f))
		};

		vector<unsigned short> indices
		{
			0, 1, 2
		};

		beak->InitFromData(vertices, indices);

		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(95, 310.5);

		meshInfo["beak"] = pair<Mesh*, glm::mat3>(beak, modelMatrix);
	}
}

Bird::~Bird()
{
	delete body;
	delete head;
	delete beak;
}

void Bird::jump()
{
	speed = 250;
}

void Bird::update(float deltaTime)
{
	y += speed * deltaTime;
	boundingCircleY += speed * deltaTime;
	speed -= deltaTime * 300;
	
	rotation += speed / 200 * deltaTime;

	if (rotation < -1.5707)
	{
		rotation = -1.5707;
	}
	else if (rotation > 1.5707)
	{
		rotation = 1.5707;
	}

	meshInfo["body"].second = glm::mat3(1);
	meshInfo["head"].second = glm::mat3(1);
	meshInfo["beak"].second = glm::mat3(1);

	meshInfo["body"].second *= Transform2D::Translate(50, y);
	meshInfo["head"].second *= Transform2D::Translate(80, y + 3);
	meshInfo["beak"].second *= Transform2D::Translate(95, y + 10.5);

	meshInfo["body"].second *= Transform2D::Translate(20, 15);
	meshInfo["body"].second *= Transform2D::Rotate(rotation);
	meshInfo["body"].second *= Transform2D::Translate(-20, -15);
	
	meshInfo["head"].second *= Transform2D::Translate(-10, 12);
	meshInfo["head"].second *= Transform2D::Rotate(rotation);
	meshInfo["head"].second *= Transform2D::Translate(10, -12);

	meshInfo["beak"].second *= Transform2D::Translate(-25, 4.5);
	meshInfo["beak"].second *= Transform2D::Rotate(rotation);
	meshInfo["beak"].second *= Transform2D::Translate(25, -4.5);
}

bool Bird::collides(Block * block)
{
	glm::vec2 ld, rd, ru, lu;

	ld = block->getPosition();
	rd = ld + glm::vec2(block->getSize().x, 0);
	ru = rd + glm::vec2(0, block->getSize().y);
	lu = ru - glm::vec2(block->getSize().x, 0);

	auto circleCenter = glm::vec2(boundingCircleX, boundingCircleY);


	auto vectorToLD = ld - circleCenter;
	auto vectorToRD = rd - circleCenter;
	auto vectorToRU = ru - circleCenter;
	auto vectorToLU = lu - circleCenter;

	float squaredDistanceLD = vectorToLD.x * vectorToLD.x + vectorToLD.y * vectorToLD.y;
	float squaredDistanceRD = vectorToRD.x * vectorToRD.x + vectorToRD.y * vectorToRD.y;
	float squaredDistanceRU = vectorToRU.x * vectorToRU.x + vectorToRU.y * vectorToRU.y;
	float squaredDistanceLU = vectorToLU.x * vectorToLU.x + vectorToLU.y * vectorToLU.y;
	float squaredRadius = radius * radius;

	return (ld.x < boundingCircleX && rd.x > boundingCircleX && (boundingCircleY + radius > ld.y && boundingCircleY - radius < lu.y)) ||
		(ld.y < boundingCircleY && lu.y > boundingCircleY && (boundingCircleX + radius > ld.x && boundingCircleX - radius < rd.x)) ||
		squaredDistanceLD < squaredRadius || squaredDistanceRD < squaredRadius || squaredDistanceRU < squaredRadius || squaredDistanceLU < squaredRadius;

}

map<string, pair<Mesh*, glm::mat3>> Bird::getMeshInfo()
{
	return meshInfo;
}
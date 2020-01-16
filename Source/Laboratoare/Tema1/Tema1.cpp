#include "Tema1.h"
#include "Transform2D.h"
#include <Core/Engine.h>
#include <cstdlib>
#include <ctime>

#include <iostream>

Tema1::Tema1()
{
	gameStarted = false;
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	numberOfBlocks = resolution.x / 350 + 2;

	closestBlockPair = 0;
	farthestBlockPair = numberOfBlocks - 1;
	score = 0;
	scoreChanged = false;

	srand(time(nullptr));

	for (int i = 0; i < numberOfBlocks; i++)
	{
		double random = ((double)rand() / RAND_MAX);
		float bottomBlockHeight = (resolution.y - 200) * random;
		float topBlockHeight = resolution.y - 200 - bottomBlockHeight;

		Block * bottomBlock, * topBlock;
		bottomBlock = new Block();
		topBlock = new Block();
		
		bottomBlock->setPosition(resolution.x + 350 * i, 0);
		bottomBlock->setSize(100, bottomBlockHeight);
		topBlock->setPosition(resolution.x + 350 * i, bottomBlockHeight + 200);
		topBlock->setSize(100, topBlockHeight);

		blocks.push_back(std::pair<Block*, Block*>(bottomBlock, topBlock));
	}
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (gameStarted)
	{
		bird.update(deltaTimeSeconds);
		for (int i = 0; i < blocks.size(); i++)
		{
			blocks[i].first->update(deltaTimeSeconds);
			blocks[i].second->update(deltaTimeSeconds);
		}

		if (bird.collides(blocks[closestBlockPair].first) || bird.collides(blocks[closestBlockPair].second))
		{
			gameStarted = false;
			cout << "Ai murit, imi pare rau :((" << endl;
		}

		auto closestBlock = blocks[closestBlockPair].first;

		if (closestBlock->getPosition().x < 50 && !scoreChanged)
		{
			score++;
			scoreChanged = true;
			cout << score << endl;
		}

		if (closestBlock->getPosition().x + closestBlock->getSize().x < 0)
		{
			auto oldFarthestBlockPosition = blocks[farthestBlockPair].first->getPosition();
			float newBlockHeight = ((double)rand() / RAND_MAX) * (window->GetResolution().y - 200);

			auto bottomBlock = blocks[closestBlockPair].first;
			auto topBlock = blocks[closestBlockPair].second;

			bottomBlock->setPosition(oldFarthestBlockPosition.x + 350, 0);
			topBlock->setPosition(oldFarthestBlockPosition.x + 350, newBlockHeight + 200);
			bottomBlock->setSize(100, newBlockHeight);
			topBlock->setSize(100, window->GetResolution().y - 200 - newBlockHeight);

			farthestBlockPair = closestBlockPair;
			closestBlockPair = (closestBlockPair + 1) % numberOfBlocks;

			scoreChanged = false;
		}
	}

	for (auto meshInfo : bird.getMeshInfo())
	{
		RenderMesh2D(meshInfo.second.first, shaders["VertexColor"], meshInfo.second.second);
	}

	for (int i = 0; i < blocks.size(); i++)
	{
		auto meshInfo1 = blocks[i].first->getMeshInfo();
		RenderMesh2D(meshInfo1.first, shaders["VertexColor"], meshInfo1.second);
		auto meshInfo2 = blocks[i].second->getMeshInfo();
		RenderMesh2D(meshInfo2.first, shaders["VertexColor"], meshInfo2.second);
	}
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		if (!gameStarted)
		{
			gameStarted = true;
		}
		bird.jump();
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

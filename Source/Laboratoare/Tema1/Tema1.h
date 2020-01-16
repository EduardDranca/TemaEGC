#pragma once

#include <Component/SimpleScene.h>
#include "Bird.h"
#include "Block.h"

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	Bird bird;
	//pairs of top and bottom blocks
	vector<std::pair<Block*, Block*>> blocks;
	glm::vec3 viteza;
	float x, y;
	bool gameStarted;
	bool scoreChanged;

	int closestBlockPair, farthestBlockPair;
	int numberOfBlocks;

	int score;

	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
};
#pragma once

#include "CameraController.h"
#include "KamataEngine.h"
#include "Player.h"

using namespace KamataEngine;

class GameScene {

public:
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	Camera camera_;

	WorldTransform worldTransform_;

	Input* input_ = nullptr;

	Model* modelPlayer_ = nullptr;

	Player* player_ = nullptr;

	CameraController* cameraController_;
};
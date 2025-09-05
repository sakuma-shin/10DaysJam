#pragma once

#include "CameraController.h"
#include "KamataEngine.h"
#include "Player.h"
#include "IScene.h"

using namespace KamataEngine;

class GameScene : public IScene {

public:
	~GameScene();


void Initialize() override;

void Update() override;

void Draw() override;

private:
	Camera camera_;

	WorldTransform worldTransform_;

	Input* input_ = nullptr;

	Model* modelPlayer_ = nullptr;

	Player* player_ = nullptr;

	CameraController* cameraController_;
};
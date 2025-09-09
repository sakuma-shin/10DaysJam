#pragma once

#include "CameraController.h"
#include "KamataEngine.h"
#include "Player.h"
#include "CameraController.h"
#include "Mapchip.
#include "IScene.h"
#include"Skydome.h"

using namespace KamataEngine;

class GameScene : public IScene {

public:
	~GameScene();


void Initialize() override;

void Update() override;

void Draw() override;

// ブロック生成
void GenerateBlocks();
void CollisionsCheck();

private:
	Camera camera_;

	WorldTransform worldTransform_;
// モデル
Model* modelPlayer_ = nullptr;
Model* modelHole_ = nullptr;
Model* modelRoad_ = nullptr
	Input* input_ = nullptr

	Model* modelPlayer_ = nullptr;

	Player* player_ = nullptr;

MapChipField* mapChipField_;

// ブロック配列
std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;
std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformHoles_;
	CameraController* cameraController_;

	// 天球
	Skydome* skydome_ = nullptr;
	uint32_t skydomeTextureHandle_ = 0u;
	KamataEngine::Model* skydomeModel_ = nullptr;
};
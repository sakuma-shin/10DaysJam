#pragma once

#include "KamataEngine.h"
#include "Player.h"
#include "CameraController.h"
#include "Mapchip.h"

using namespace KamataEngine;

class GameScene {

public:

~GameScene();

void Initialize();

void Update();

void Draw();

// ブロック生成
void GenerateBlocks();
void CollisionsCheck();

private:

Camera camera_;

WorldTransform worldTransform_;

Input* input_ = nullptr;

// モデル
Model* modelPlayer_ = nullptr;
Model* modelHole_ = nullptr;
Model* modelRoad_ = nullptr;

Player* player_ = nullptr;

CameraController* cameraController_;

MapChipField* mapChipField_;

// ブロック配列
std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;
std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformHoles_;

};
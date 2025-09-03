#pragma once

#include "KamataEngine.h"

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


};
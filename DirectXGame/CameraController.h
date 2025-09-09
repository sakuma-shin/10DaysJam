#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

class Player;

class CameraController {

public:

void Initialize();

void Update();

void SetTarget(Player* target) { target_ = target; }

void SetCamera(Camera* camera) { camera_ = camera; }

void Reset();

private:

Camera* camera_ = nullptr;

Player* target_ = nullptr;

Vector3 targetOffset_ = {0, 10.0f, -30.0f};

Vector3 targetPosition_;

static inline const float kInterpolationRate_ = 0.05f;

};
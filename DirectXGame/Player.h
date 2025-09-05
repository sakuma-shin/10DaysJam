#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Player {

public:
	~Player();

	void Initialize(Model* model);

	void Update();

	void Draw(Camera& camera);

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Input* input_ = nullptr;

	float velocityY_ = 0.0f;
	bool isOnGround_ = true;

	const float gravity_ = -0.10f;
	const float jumpPower_ = 2.0f;
	const float groundHeight_ = 0.0f;

};
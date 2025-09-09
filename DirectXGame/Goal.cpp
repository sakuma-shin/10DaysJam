#include "Goal.h"
using namespace KamataEngine;

void Goal::Initialize(Model* model, uint32_t textureHandle,KamataEngine::Vector3 position) {
	assert(model);
	worldTransform_.Initialize();
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.translation_ = position;
}

void Goal::Update() { worldTransform_.UpdateMatrix(); }

void Goal::Draw(Camera& camera) { model_->Draw(worldTransform_, camera, textureHandle_); }

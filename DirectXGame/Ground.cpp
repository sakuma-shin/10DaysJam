#include "Ground.h"

using namespace KamataEngine;

void Ground::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	worldTransform_.Initialize();
	model_ = model;
	textureHandle_ = textureHandle;
}

void Ground::Update() {}

void Ground::Draw(Camera& camera) { model_->Draw(worldTransform_, camera, textureHandle_); }

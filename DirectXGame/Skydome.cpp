#include "Skydome.h"

using namespace KamataEngine;

void Skydome::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	worldTransform_.Initialize();
	model_ = model;
	textureHandle_ = textureHandle;
}

void Skydome::Update() {}

void Skydome::Draw(Camera& camera) { model_->Draw(worldTransform_, camera, textureHandle_); }

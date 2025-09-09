#include "ResultSkydome.h"

void ResultSkydome::Initialize(Model* model, Camera* camera) {

	worldTransform_.Initialize();
	model_ = model;
	camera_ = camera;

}

void ResultSkydome::Update() {}

void ResultSkydome::Draw() {

	model_->Draw(worldTransform_, *camera_);

}

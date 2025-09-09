#include "ResultScene.h"
using namespace KamataEngine;

void ResultScene::Initialize() {

	modelSkydome_ = Model::CreateFromOBJ("resultSkydome");

	resultSkydome_ = new ResultSkydome();
	resultSkydome_->Initialize(modelSkydome_, &camera_);

	worldTransform_.Initialize();

	camera_.Initialize();

	input_ = Input::GetInstance();
}

void ResultScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = TITLE;
	}

	resultSkydome_->Update();

}

void ResultScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw(dxCommon->GetCommandList());

	resultSkydome_->Draw();

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}

ResultScene::~ResultScene() {}
#include "ResultScene.h"
using namespace KamataEngine;

void ResultScene::Initialize() {

	worldTransform_.Initialize();

	camera_.Initialize();

	input_ = Input::GetInstance();
}

void ResultScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = TITLE;
	}
}

void ResultScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}

ResultScene::~ResultScene() {}
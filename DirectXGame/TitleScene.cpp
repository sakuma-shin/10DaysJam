#include "TitleScene.h"
using namespace KamataEngine;

void TitleScene::Initialize() {

	worldTransform_.Initialize();

	camera_.Initialize();

	input_=Input::GetInstance();
}

void TitleScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = STAGE;
	}

}

void TitleScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();


	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}

TitleScene::~TitleScene() {
	
}

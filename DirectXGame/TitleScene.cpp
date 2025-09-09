#include "TitleScene.h"
using namespace KamataEngine;

void TitleScene::Initialize() {

	modelSkydome_ = Model::CreateFromOBJ("titleSkydome");

	titleSkydome_ = new TitleSkydome();
	titleSkydome_->Initialize(modelSkydome_, &camera_);

	worldTransform_.Initialize();

	camera_.Initialize();

	input_ = Input::GetInstance();
}

void TitleScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = STAGE;
	}

	titleSkydome_->Update();

}

void TitleScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw(dxCommon->GetCommandList());

	titleSkydome_->Draw();

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}

TitleScene::~TitleScene() {}
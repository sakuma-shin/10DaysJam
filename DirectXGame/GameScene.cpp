#include "GameScene.h"
using namespace KamataEngine;

GameScene::~GameScene() {
}

void GameScene::Initialize() {

	worldTransform_.Initialize();

	camera_.Initialize();

	input_ = Input::GetInstance();

	

}

void GameScene::Update() {

	if (input_->TriggerKey(DIK_RETURN)) {

		sceneNo = RESULT;
	}
	
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//後景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());


	//後景スプライト描画後処理
	Sprite::PostDraw();

	//深度クリア
	dxCommon->ClearDepthBuffer();

	//前景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// 前景スプライト描画後処理
	Sprite::PostDraw();
}

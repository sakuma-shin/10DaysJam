#include "GameScene.h"

GameScene::~GameScene() {

	delete modelPlayer_;
	delete player_;

}

void GameScene::Initialize() {

	modelPlayer_ = Model::CreateFromOBJ("Player");

	camera_.Initialize();

	player_ = new Player();

	player_->Initialize(modelPlayer_);

	input_ = Input::GetInstance();

	worldTransform_.Initialize();

}

void GameScene::Update() {

	player_->Update(); 

	if (input_->TriggerKey(DIK_RETURN)) {

		sceneNo = RESULT;
	}

}

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw(dxCommon->GetCommandList());

	player_->Draw(camera_);

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

}

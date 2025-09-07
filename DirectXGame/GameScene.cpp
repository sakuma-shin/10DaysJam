#include "GameScene.h"

GameScene::~GameScene() {

	delete modelPlayer_;
	delete player_;
	delete skydome_;
	delete skydomeModel_;
}

void GameScene::Initialize() {

	modelPlayer_ = Model::CreateFromOBJ("Player");

	camera_.Initialize();

	player_ = new Player();
	player_->Initialize(modelPlayer_);

	cameraController_ = new CameraController();
	cameraController_->SetCamera(&camera_);
	cameraController_->SetTarget(player_);
	cameraController_->Initialize();
	cameraController_->Reset();

	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	skydomeTextureHandle_ = TextureManager::Load("sky_sphere.png");

	skydomeModel_ = Model::CreateFromOBJ("skyDome", true);

	// 天球
	skydome_ = new Skydome();
	// 初期化
	skydome_->Initialize(skydomeModel_, skydomeTextureHandle_);
}

void GameScene::Update() {

	player_->Update();

	if (input_->TriggerKey(DIK_RETURN)) {

		sceneNo = RESULT;
	}

	cameraController_->Update();
}

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw(dxCommon->GetCommandList());

	skydome_->Draw(camera_);
	player_->Draw(camera_);
	

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}
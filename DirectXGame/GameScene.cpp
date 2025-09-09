#include "GameScene.h"

GameScene::~GameScene() {

	delete modelPlayer_;
	delete player_;
	delete skydome_;
	delete skydomeModel_;
}

void GameScene::Initialize() {

	modelPlayer_ = Model::CreateFromOBJ("car");

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

	groundTextureHandle_ = TextureManager::Load("Ground.png");
	groundModel_ = Model::CreateFromOBJ("Ground", true);

	goalModel_ = Model::CreateFromOBJ("Goal", true);
	goalTextureHandle_ = TextureManager::Load("goal.png");

	// 天球
	skydome_ = new Skydome();
	// 初期化
	skydome_->Initialize(skydomeModel_, skydomeTextureHandle_);

	ground_ = new Ground();
	//初期化
	ground_->Initialize(groundModel_, groundTextureHandle_);

	Vector3 goalPos = {0.0f, 0.0f, 150.0f};
	goal_ = new Goal();
	goal_->Initialize(goalModel_, goalTextureHandle_, goalPos);
}

void GameScene::Update() {

	player_->Update();
	goal_->Update();

	if (input_->TriggerKey(DIK_RETURN)) {

		sceneNo = RESULT;
	}

	if (input_->TriggerKey(DIK_1)) {

		sceneNo = OVER;
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
	ground_->Draw(camera_);
	goal_->Draw(camera_);
	player_->Draw(camera_);
	

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}
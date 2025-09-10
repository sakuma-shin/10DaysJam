#include "GameScene.h"

GameScene::~GameScene() {

	delete modelPlayer_;
	delete player_;
	delete skydome_;
	delete skydomeModel_;
	delete ground_;
	delete groundModel_;
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

	goalModel_ = Model::CreateFromOBJ("goal", true);
	goalTextureHandle_ = TextureManager::Load("goal.png");

	wallModel_ = Model::CreateFromOBJ("wall", true);

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

	for (int i = 0; i < 3; i++) {
		wallPos_[i].Initialize();
		wallPos_[i].scale_ = {4.0f, 2.0f, 4.0f};
	}

	wallPos_[0].translation_ = {-17.0f, 0.0f, 130.0f};
	wallPos_[1].translation_ = {17.0f, 0.0f, 90.0f};
	wallPos_[2].translation_ = {0.0f, 0.0f, 50.0f};

	for (int i = 0; i < 3; i++) {
		wallPos_[i].UpdateMatrix();
	}
}

void GameScene::Update() {

	player_->Update();
	goal_->Update();

	Vector3 playerPos = player_->GetWorldTransform().translation_;
	Vector3 goalPos = goal_->GetGoalPos();

	if (playerPos.z >= goalPos.z) {
		sceneNo = RESULT;
	}

	if (player_->isDead() == true) {

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
	for (int i = 0; i < 3; i++) {
		wallModel_->Draw(wallPos_[i], camera_);
	}
	player_->Draw(camera_);
	

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}
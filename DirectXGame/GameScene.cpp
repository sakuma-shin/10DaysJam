#include "GameScene.h"
#include "Affin.h"

using namespace KamataEngine;

GameScene::~GameScene() {

	delete modelPlayer_;
	delete player_;

	for (std::vector<WorldTransform*> worldTransformBlockHeight : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockWidth : worldTransformBlockHeight) {
			delete worldTransformBlockWidth;
		}
	}

	for (std::vector<WorldTransform*> worldTransformBlockHeight : worldTransformHoles_) {
		for (WorldTransform* worldTransformBlockWidth : worldTransformBlockHeight) {
			delete worldTransformBlockWidth;
		}
	}

	worldTransformBlocks_.clear();
	worldTransformHoles_.clear();

	delete modelHole_;
	delete modelRoad_;
}

void GameScene::Initialize() {

	modelPlayer_ = Model::CreateFromOBJ("Player");
	modelRoad_ = Model::CreateFromOBJ("cube"); // 後で変更
	modelHole_ = Model::CreateFromOBJ("cube"); // 後で変更

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

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/proto2.csv");

	GenerateBlocks();
}

void GameScene::Update() {

	player_->Update(); 

	cameraController_->Update();

	for (std::vector<WorldTransform*> worldTransformBlockHeight : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockWidth : worldTransformBlockHeight) {
			if (!worldTransformBlockWidth)
				continue;

			// アフィン変換行列の作成
			worldTransformBlockWidth->matWorld_ = MakeAffineMatrix(worldTransformBlockWidth->scale_, worldTransformBlockWidth->rotation_, worldTransformBlockWidth->translation_);

			// 定数バッファに転送
			worldTransformBlockWidth->TransferMatrix();
		}
	}

	for (std::vector<WorldTransform*> worldTransformBlockHeight : worldTransformHoles_) {
		for (WorldTransform* worldTransformBlockWidth : worldTransformBlockHeight) {
			if (!worldTransformBlockWidth)
				continue;

			// アフィン変換行列の作成
			worldTransformBlockWidth->matWorld_ = MakeAffineMatrix(worldTransformBlockWidth->scale_, worldTransformBlockWidth->rotation_, worldTransformBlockWidth->translation_);

			// 定数バッファに転送
			worldTransformBlockWidth->TransferMatrix();
		}
	}
}

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw(dxCommon->GetCommandList());

	player_->Draw(camera_);

	for (std::vector<WorldTransform*> worldTransformBlockHeight : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockWidth : worldTransformBlockHeight) {
			if (!worldTransformBlockWidth)
				continue;

			modelRoad_->Draw(*worldTransformBlockWidth, camera_);
		}
	}

	for (std::vector<WorldTransform*> worldTransformBlockHeight : worldTransformHoles_) {
		for (WorldTransform* worldTransformBlockWidth : worldTransformBlockHeight) {
			if (!worldTransformBlockWidth)
				continue;

			modelHole_->Draw(*worldTransformBlockWidth, camera_);
		}
	}

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

}

void GameScene::GenerateBlocks() { 
	uint32_t numBlockVirticle = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する
	worldTransformBlocks_.resize(numBlockVirticle);
	worldTransformHoles_.resize(numBlockVirticle);

	for (uint32_t i = 0; i < numBlockVirticle; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
		worldTransformHoles_[i].resize(numBlockHorizontal);
	}

	for (uint32_t i = 0; i < numBlockVirticle; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kRoad) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}

			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kHole) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformHoles_[i][j] = worldTransform;
				worldTransformHoles_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}
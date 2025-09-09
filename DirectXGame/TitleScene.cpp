#include "TitleScene.h"
using namespace KamataEngine;

void TitleScene::Initialize() {

	modelSkydome_ = Model::CreateFromOBJ("titleSkydome");
	textureHandle_ = TextureManager::Load("sprite/titleSprite.png");
	sprite_ = Sprite::Create(textureHandle_, {190, 0});
	
	startTextureHandle_ = TextureManager::Load("sprite/titleStartSprite.png"); 
	startSprite_ = Sprite::Create(startTextureHandle_, {290, 500});

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

	const float blinkInterval = 0.7f;
	blinkTimer_ += 1.0f / 60.0f;

	if (blinkTimer_ >= blinkInterval) {
		isStartVisible_ = !isStartVisible_;
		blinkTimer_ = 0.0f;
	}

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

	sprite_->Draw();
	if (isStartVisible_) {
		startSprite_->Draw();
	}

	Sprite::PostDraw();
}

TitleScene::~TitleScene() {}
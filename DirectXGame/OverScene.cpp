#include "OverScene.h"
using namespace KamataEngine;

void OverScene::Initialize() {

	modelSkydome_ = Model::CreateFromOBJ("resultSkydome");
	clearTextureHandle_ = TextureManager::Load("sprite/clearSprite.png");
	clearSprite_ = Sprite::Create(clearTextureHandle_, {190, 100});

	overTextureHandle_ = TextureManager::Load("sprite/overSprite.png");
	overSprite_ = Sprite::Create(overTextureHandle_, {190, 100});

	enterTextureHandle_ = TextureManager::Load("sprite/resultEnter.png");
	enterSprite_ = Sprite::Create(enterTextureHandle_, {220, 500});

	resultSkydome_ = new ResultSkydome();
	resultSkydome_->Initialize(modelSkydome_, &camera_);

	worldTransform_.Initialize();

	camera_.Initialize();

	input_ = Input::GetInstance();
}

void OverScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = TITLE;
	}

	resultSkydome_->Update();

	const float blinkInterval = 0.7f;
	blinkTimer_ += 1.0f / 60.0f;

	if (blinkTimer_ >= blinkInterval) {
		isStartVisible_ = !isStartVisible_;
		blinkTimer_ = 0.0f;
	}
}

void OverScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw(dxCommon->GetCommandList());

	resultSkydome_->Draw();

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	overSprite_->Draw();
	if (isStartVisible_) {
		enterSprite_->Draw();
	}

	Sprite::PostDraw();
}

OverScene::~OverScene() {}
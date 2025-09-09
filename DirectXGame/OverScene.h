#pragma once
#include "IScene.h"
#include "KamataEngine.h"
#include "ResultSkydome.h"
class OverScene : public IScene {
public:
	void Initialize() override;

	void Update() override;

	void Draw() override;

	~OverScene();

private:
	KamataEngine::Camera camera_;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Input* input_ = nullptr;

	ResultSkydome* resultSkydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	uint32_t clearTextureHandle_ = 0;
	Sprite* clearSprite_ = nullptr;

	uint32_t overTextureHandle_ = 0;
	Sprite* overSprite_ = nullptr;

	uint32_t enterTextureHandle_ = 0;
	Sprite* enterSprite_ = nullptr;

	float blinkTimer_ = 0.0f;
	bool isStartVisible_ = true;
};

#pragma once
#include "IScene.h"
#include "KamataEngine.h"
#include "ResultSkydome.h"

class ResultScene : public IScene {
public:
	void Initialize() override;

	void Update() override;

	void Draw() override;

	~ResultScene();

private:
	KamataEngine::Camera camera_;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Input* input_ = nullptr;

	ResultSkydome* resultSkydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

};
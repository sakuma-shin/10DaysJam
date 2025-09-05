#pragma once
#include "IScene.h"
#include "KamataEngine.h"
class TitleScene : public IScene {
public:
	void Initialize() override;

	void Update() override;

	void Draw() override;

	~TitleScene();

private:
	KamataEngine::Camera camera_;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Input* input_;
};
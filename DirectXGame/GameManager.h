#pragma once

#include "GameScene.h"
#include "IScene.h"
#include "KamataEngine.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include <memory>
using namespace KamataEngine;

class GameManager {
private:
	// シーンを保持するメンバ関数
	std::unique_ptr<IScene> sceneArr_[3];

	int currentSceneNo_;
	int prevSceneNo_;

	// DirectXCommonインスタンスの取得
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;

	// DirectXCommonクラスが管理している、ウインドウの幅と高さの取得
	int32_t w = 0u;
	int32_t h = 0u;

public:
	GameManager();
	~GameManager();

	int Run();
};
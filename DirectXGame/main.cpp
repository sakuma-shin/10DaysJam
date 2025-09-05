#include "GameManager.h"
#include <KamataEngine.h>

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// 汎用機能の初期化
	WinApp* win = WinApp::GetInstance();
	win->CreateGameWindow();

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	Input* input = Input::GetInstance();
	input->Initialize();

	Audio* audio = Audio::GetInstance();
	audio->Initialize();

	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	Model::StaticInitialize();

	AxisIndicator* axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	PrimitiveDrawer* primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();

	// GameManagerの実行
	GameManager* gameManager = new GameManager();
	gameManager->Run();

	// 終了処理
	delete gameManager; // ゲームマネージャーの解放

	// 静的インスタンスの解放
	Model::StaticFinalize();
	audio->Finalize();
	imguiManager->Finalize();

	win->TerminateGameWindow();

	return 0;
}
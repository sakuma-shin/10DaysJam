// GameManager.cpp (修正後)

#include "GameManager.h"

GameManager::GameManager() {
	win = WinApp::GetInstance();
	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	axisIndicator = AxisIndicator::GetInstance();
	primitiveDrawer = PrimitiveDrawer::GetInstance();

	// 各シーンの配列
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[STAGE] = std::make_unique<GameScene>();
	sceneArr_[RESULT] = std::make_unique<ResultScene>();

	currentSceneNo_ = TITLE;

	// ゲーム開始時に最初にロードされるシーンのInitializeをここで呼び出す
	sceneArr_[currentSceneNo_]->Initialize();
}

GameManager::~GameManager() {}

int GameManager::Run() {
	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// シーンのチェック
		prevSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo(); // IScene::sceneNoを直接参照する

		// シーン変更チェック
		if (prevSceneNo_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Initialize();
		}

		// ImGui受付開始
		ImGuiManager::GetInstance()->Begin();

		// 入力関連の毎フレーム処理
		input->Update();

		// 軸表示の更新
		axisIndicator->Update();

		// シーンごとの更新処理
		sceneArr_[currentSceneNo_]->Update();

		// ImGui受付終了
		ImGuiManager::GetInstance()->End();

		// 描画開始
		dxCommon->PreDraw();

		// シーンごとの描画処理
		sceneArr_[currentSceneNo_]->Draw();

		// 軸表示の描画
		axisIndicator->Draw();

		// プリミティブ描画のリセット
		primitiveDrawer->Reset();

		// ImGui描画
		ImGuiManager::GetInstance()->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}


	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	return 0;
}
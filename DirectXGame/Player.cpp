#include "Player.h"

Player::~Player() {}

void Player::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.translation_.y = groundHeight_;
}

void Player::Update() {
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;
	const float kAutoSpeedZ = 0.1f;

	// --- 左右移動 ---
	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	// --- 自動前進 ---
	move.z += kAutoSpeedZ;

	// --- ジャンプ処理 ---
	if (isOnGround_ && input_->TriggerKey(DIK_SPACE)) {
		velocityY_ = jumpPower_;
		isOnGround_ = false;
	}

	// 重力を加算
	velocityY_ += gravity_;
	move.y += velocityY_;

	// --- 座標移動 ---
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// 着地判定
	if (worldTransform_.translation_.y <= groundHeight_) {
		worldTransform_.translation_.y = groundHeight_;
		velocityY_ = 0.0f;
		isOnGround_ = true;
	}

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }

#include "Player.h"

Player::~Player() {}

void Player::Initialize(Model* model) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	input_ = Input::GetInstance();


}

void Player::Update() {

	Vector3 move = {0, 0, 0};

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;
	const float kAutoSpeedY = 0.1f; 

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_A)) {

		move.x -= kCharacterSpeed;
	}

	if (input_->PushKey(DIK_D)) {

		move.x += kCharacterSpeed;
	}

	  move.y += kAutoSpeedY;

	// 座標移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();

}

void Player::Draw(Camera& camera) {

	model_->Draw(worldTransform_, camera);

}

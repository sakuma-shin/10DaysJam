#define NOMINMAX
#include "Player.h"
#include "Mapchip.h"
#include <algorithm>
#include <cassert>
#include <numbers>

using namespace KamataEngine::MathUtility;

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
	
	if(isDead_ == false){
		move.y += kAutoSpeedY;
	}

	// 座標移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	// 衝突情報を初期化
	CollisionMapInfo collisionMapInfo;
	// 移動量に速度の値をコピー
	collisionMapInfo.movement_ = move;

	worldTransform_.rotation_.x = -90.0f;

	MapCollisionDown(collisionMapInfo);

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();

}

void Player::Draw(Camera& camera) {

	model_->Draw(worldTransform_, camera);

}

void Player::MapCollisionDown(CollisionMapInfo info) {
	// 移動後４つの角の座標
	std::array<Vector3, kNumCorner> positionsNew{};

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + Vector3(0, info.movement_.y, 0), static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	MapChipType mapChipTypeNext;

	// 真上の当たり判定を行う
	bool hit = false;
	// 左下点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);
	if (mapChipType == MapChipType::kRoad && mapChipTypeNext != MapChipType::kRoad) {
		hit = true;
	}
	if (mapChipType == MapChipType::kHole) {
		isDead_ = true;
	}

	// 右下点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);
	if (mapChipType == MapChipType::kRoad && mapChipTypeNext != MapChipType::kRoad) {
		hit = true;
	}
	if (mapChipType == MapChipType::kHole) {
		isDead_ = true;
	}

	// ブロックにヒット？
	if (hit) {
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(0, -kHeight / 2.0f, 0));
		if (indexSetNow.yIndex != indexSet.yIndex) {
			// めり込みを排除する方向に移動量を設定する
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.movement_ + Vector3(0, -kHeight / 2.0f, 0));
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			info.movement_.y = std::min(0.0f, (rect.top - worldTransform_.translation_.y) + ((kHeight / 2.0f) + kBlank));
			// 地面に当たったことを記録する
			info.LandingFlag = true;
		}
	}
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {
	Vector3 offsetTable[kNumCorner] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0}, // kRightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0}, // kLeftBottom
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0}, // kRightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0}  // kleftTop
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}

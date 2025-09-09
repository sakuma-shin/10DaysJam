#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class MapChipField;

// 角
enum Corner {
	kRightBottom, // 右下
	kLeftBottom,  // 左下
	kRightTop,    // 右上
	kLeftTop,     // 左上

	kNumCorner // 要素数
};

class Player {

public:
	~Player();

	void Initialize(Model* model);

	void Update();

	void Draw(Camera& camera);

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	// マップとのあたり判定情報
	struct CollisionMapInfo {
		bool LandingFlag = false;
		Vector3 movement_;
	};

	void MapCollisionDown(CollisionMapInfo info);

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	// デスフラグのGetter
	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Input* input_ = nullptr;

	// デスフラグ
	bool isDead_ = false;

	MapChipField* mapChipField_ = nullptr;
	
	static inline const float kWidth = 1.0f;

	static inline const float kHeight = 1.0f;

	static inline const float kBlank = 18.0f;
};
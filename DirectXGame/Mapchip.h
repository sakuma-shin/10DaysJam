#include "KamataEngine.h"
#pragma once

enum class MapChipType {
	kHole, // 穴
	kRoad, // 道
	kJump, // ジャンプ台
	kWall, // 壁
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {
public:
	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};

	// 範囲矩形
	struct Rect {
		float left;
		float right;
		float top;
		float bottom;
	};

	// 1ブロックのサイズ
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;

	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20; // 縦の個数
	static inline const uint32_t kNumBlockHorizontal = 15; // 横の個数

	MapChipData mapChipData_;

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical() const;
	uint32_t GetNumBlockHorizontal() const;

	IndexSet GetMapChipIndexSetByPosition(const KamataEngine::Vector3& position);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

private:
	void ResetMapChipData();

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* camera_ = nullptr;
	// モデル
	KamataEngine::Model* model_ = nullptr;
};

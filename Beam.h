#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Beam {
public:
	// �R���X�g���N�^
	Beam();
	// �f�X�g���N�^
	~Beam();

	// ������
	void Initialize(ViewProjection viewProjection);
	// �X�V
	void Update();
	// 3D�`��
	void Draw3D();
	// �C���v�b�g�N���X
	Input* input_ = nullptr;

private:
	ViewProjection viewProjection_;
	// �r�[��
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = nullptr;
	WorldTransform worldTransformBeam_;
};

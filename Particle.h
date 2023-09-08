#pragma once
#include "../Resources/Effect/IEffect.h"

// �G�t�F�N�g�̖��O���N���X����
class Particle
	: public IEffect {
public:	// �����o�֐�
	Particle(Model* model, Vector3 position);
	~Particle();

	// �G�t�F�N�g�̏������I�������K��isEnd��true�Ɂi�ϐ���IEffect.h�Œ�`�ς݁j
	// Update�ADraw�͍ŏ���isEnd��true�Ȃ��return���邱��

	void Initialize() override;	// ������
	void Update() override;	// �X�V
	void Draw(const ViewProjection& viewProjection) override;	// �`��

private: // �����o�萔

	/*const float kUpperMoveFrame = 0.0f;*/

	//�C�[�W���O�I������
	const float kUpperMoveHeight = 60.0f;
	/*const int kUpperMovetime = 30;*/

	//�u���b�N���Ŏ���
	const int blockEndtime = 90;

	//�u���b�N�X�^�[�g�n�_
	const float blockStart = 0.0f;

	//�u���b�N�ŏI���B�n�_
	const float blockEnd = 10.0f;

	//�p�[�e�B�N���z��
	const int ParticlCount = 100;

private: // �����o�ϐ�

	// �u���b�N�̃��f��
	Model* model_ = nullptr;
	// �u���b�N�̃��[���h�g�����X�t�H�[��
	WorldTransform transform_;

	// �o�߃t���[��
	int elapsedFrame_ = 0;

	// �e�N�X�`��
	uint32_t textureNum_;

};
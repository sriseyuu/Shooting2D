//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FBaseScene.h							
//													
// �T�@�@�v�F�x�[�X�V�[���̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 17							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

#include <SpriteBatch.h>

#include <Keyboard.h>
class BaseScene
{
public:

	// �f�X�g���N�^
	virtual ~BaseScene() {}
	// �X�V����
	virtual void Update() = 0;
	// �`�揈��
	virtual void Render(DirectX::SpriteBatch* spriteBatch) = 0;

protected:
	std::unique_ptr<DirectX::Keyboard> keyboard = std::make_unique<DirectX::Keyboard>();
};
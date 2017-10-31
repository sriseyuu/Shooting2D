//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FGameScene.h							
//													
// �T�@�@�v�F�Q�[���V�[���̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 25						
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "BaseScene.h"
#include "Sprite2D.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class TitleScene : public BaseScene
{
public:
	TitleScene() : BaseScene() {}
	TitleScene(ID3D11Device* device, ID3D11DeviceContext* context);
	~TitleScene() {}
	void Update();
	void Render(DirectX::SpriteBatch* spriteBatch);

private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

};
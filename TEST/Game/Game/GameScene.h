//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FGameScene.h							
//													
// �T�@�@�v�F�Q�[���V�[���̃w�b�_�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 17							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "BaseScene.h"
#include "Sprite2D.h"
#include "Player.h"
#include <vector>

class GameScene : public BaseScene
{
public:
	GameScene(ID3D11Device* device,ID3D11DeviceContext* context);

	void Update();
	void Render(DirectX::SpriteBatch* spriteBatch);


private:
	Player* m_Player;
};
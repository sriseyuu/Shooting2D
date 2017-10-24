//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// ���@�@�O�FGameScene.cpp							
//													
// �T�@�@�v�F�Q�[���V�[���̃\�[�X�t�@�C��			
//													
// �� �� �ҁFYuga Yamamoto							
//													
// �X�V�����F2017 / 10 / 17							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "GameScene.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

GameScene::GameScene(ID3D11Device * device, ID3D11DeviceContext * context)
{
	player.SetTexture(device,L"Resources/Player.png");

}

void GameScene::Update()
{
	auto kb = keyboard->GetState();

	Vector2 spd = Vector2::Zero;
	
	if (kb.Up) {
		spd.y -= 1.0f;
	}
	if (kb.Down) {
		spd.y += 1.0f;
	}
	if (kb.Left) {
		spd.x -= 1.0f;
	}
	if (kb.Right) {
		spd.x += 1.0f;
	}
	if (kb.Enter) {

	}
	player.Translate(spd);

	player.Update();
}

void GameScene::Render(SpriteBatch* spriteBatch)
{
	player.Render(spriteBatch);
}

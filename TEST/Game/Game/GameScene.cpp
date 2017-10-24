//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：GameScene.cpp							
//													
// 概　　要：ゲームシーンのソースファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 17							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "GameScene.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

GameScene::GameScene(ID3D11Device * device, ID3D11DeviceContext * context)
{
	m_Player = new Player(device);
}

void GameScene::Update()
{
	auto KeyState = keyboard->GetState();

	m_Player->Update(KeyState);
}

void GameScene::Render(SpriteBatch* spriteBatch)
{
	m_Player->Render(spriteBatch);
}

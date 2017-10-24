//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：GameScene.h							
//													
// 概　　要：ゲームシーンのヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 17							
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
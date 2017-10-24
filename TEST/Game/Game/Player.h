//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Player.h							
//													
// 概　　要：プレイヤのヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 24							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "Sprite2D.h"

#include <Keyboard.h>

class Player
{
public:
	const float MOVE_SPD = 2.5f;

	// コンストラクタ
	Player(ID3D11Device * device);

	// 更新処理
	void Update(DirectX::Keyboard::State state);

	void Render(DirectX::SpriteBatch* spriteBatch);

private:
	Sprite2D m_Player;
};

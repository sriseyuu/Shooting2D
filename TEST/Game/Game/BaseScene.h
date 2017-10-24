//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：BaseScene.h							
//													
// 概　　要：ベースシーンのヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 17							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

#include <SpriteBatch.h>

#include <Keyboard.h>
class BaseScene
{
public:

	// デストラクタ
	virtual ~BaseScene() {}
	// 更新処理
	virtual void Update() = 0;
	// 描画処理
	virtual void Render(DirectX::SpriteBatch* spriteBatch) = 0;

protected:
	std::unique_ptr<DirectX::Keyboard> keyboard = std::make_unique<DirectX::Keyboard>();
};
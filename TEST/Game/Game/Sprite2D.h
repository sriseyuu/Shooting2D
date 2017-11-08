//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Sprite2D.h							
//													
// 概　　要：2Dスプライトのヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 24							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#include <SimpleMath.h>
#include <SpriteBatch.h>

#include <CommonStates.h>

#include <WICTextureLoader.h>

class Sprite2D
{
public:
	~Sprite2D();

	// テクスチャの設定
	void SetTexture(ID3D11Device* device, const wchar_t* filename);
	void SetTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);

	virtual void Update();

	virtual void Render(DirectX::SpriteBatch* spriteBatch);

	// 画像の座標の取得と設定
	void SetPos(DirectX::SimpleMath::Vector2 pos) { m_screenPos = pos; }
	void SetPos(float posx, float posy) { m_screenPos = DirectX::SimpleMath::Vector2(posx, posy); }
	DirectX::SimpleMath::Vector2 GetPos() { return m_screenPos; }

	// 回転角の設定
	void SetRotation(float rot) { m_rot = rot; }

	// 画像の大きさの取得
	DirectX::SimpleMath::Vector2 GetTextureSize() { return m_origin * 2; }

	// プレイヤのフレーム移動(引数：移動距離)
	void Translate(DirectX::SimpleMath::Vector2 vec);
	// プレイヤのフレーム回転
	void Rotate(float rot) { m_rot += rot; }
	
	void SetColor(DirectX::SimpleMath::Color color) { col = color; }
private:
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// 座標
	DirectX::SimpleMath::Vector2 m_screenPos;
	// 中心座標
	DirectX::SimpleMath::Vector2 m_origin;
	// 回転角
	float m_rot = 0.0f;
	// iro
	DirectX::SimpleMath::Color col = DirectX::Colors::White;
};
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
class Sprite2D
{
public:
	// テクスチャの設定
	void SetTexture(ID3D11Device* device, const wchar_t* filename);

	void Update();

	void Render(DirectX::SpriteBatch* spriteBatch);

	// 画像の座標の取得と設定
	void SetPos(DirectX::SimpleMath::Vector2 pos) { m_screenPos = pos; }
	DirectX::SimpleMath::Vector3 GetPos() { return m_screenPos; }

	void Translate(DirectX::SimpleMath::Vector2 vec) { m_screenPos += vec; }
private:
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// 座標
	DirectX::SimpleMath::Vector2 m_screenPos;
	// 
	DirectX::SimpleMath::Vector2 m_origin;
};
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Sprite2D.cpp							
//													
// 概　　要：2Dスプライトのソースファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 24							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Sprite2D.h"
#include <WICTextureLoader.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

Sprite2D::~Sprite2D()
{
	// exit(1);
}

void Sprite2D::SetTexture(ID3D11Device* device, const wchar_t* filename)
{
	ComPtr<ID3D11Resource> resource;

	CreateWICTextureFromFile(device, filename, resource.GetAddressOf(),
		m_texture.ReleaseAndGetAddressOf());

	ComPtr<ID3D11Texture2D> tex;
	resource.As(&tex);

	CD3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);

	m_origin.x = float(texDesc.Width / 2);
	m_origin.y = float(texDesc.Height / 2);
}

void Sprite2D::SetTexture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
{
	m_texture = texture;
}

void Sprite2D::Update()
{

}

void Sprite2D::Render(DirectX::SpriteBatch* spriteBatch)
{
	spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White,
		m_rot, m_origin);
}

void Sprite2D::Translate(DirectX::SimpleMath::Vector2 vec)
{
	// 移動量のベクトル
	Vector2 moveV(vec);
	// 移動ベクトルを自機の角度分回転させる

	Matrix rotmat = Matrix::CreateRotationZ(m_rot);
	moveV = Vector2::TransformNormal(moveV, rotmat);
	// 自機の座標を移動
	m_screenPos += moveV;
}

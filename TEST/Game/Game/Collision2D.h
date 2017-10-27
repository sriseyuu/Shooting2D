//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Collision2D.h							
//													
// 概　　要：2D当たり判定のヘッダファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 25							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include<d3d11.h>
#include<SimpleMath.h>

class Circle2D
{
public:
	// 円の当たり判定の現在座標
	DirectX::SimpleMath::Vector2 m_pos;

	// 円の半径
	float m_Radius = 1.0f;
};

bool OnCollision2DCircle_Circle(Circle2D _circle1, Circle2D _circle2);
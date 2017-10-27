//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//													
// 名　　前：Collision2D.cpp							
//													
// 概　　要：2D当たり判定のソースファイル			
//													
// 作 成 者：Yuga Yamamoto							
//													
// 更新日時：2017 / 10 / 25							
//													
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Collision2D.h"

bool OnCollision2DCircle_Circle(Circle2D _circle1, Circle2D _circle2)
{
	// 2つの半径の和
	float r = _circle1.m_Radius + _circle2.m_Radius;

	// 2つの円のx座標の差（2点間のx座標の距離）
	float x = _circle1.m_pos.x - _circle2.m_pos.x;
	// 2つの円のy座標の差（2点間のy座標の距離）
	float y = _circle1.m_pos.y - _circle2.m_pos.y;

	// 2つの円があたっていたらtrueを返し、あたっていなければfalseを返す
	return (r * r >= x * x + y * y);
}

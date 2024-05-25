#pragma once
#include<Siv3D.hpp>
#include "BaseWindow.h"

class WindowCircle : public BaseWindow {
public:
	//コンストラクタ
	WindowCircle(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
	: BaseWindow(windowPos, windowSize, batuSize, startTime)
	{
		moveKind = MoveKind::Circle;
	}
	
	//行動(ここに広告の動きを記述してもらう)
	void act()override {
		m_vel = { Cos(t)*200,Sin(t)*200};
		t=t+0.01;
	}

private:
	//変数とかを宣言するときはここ
	double t = 0;

};

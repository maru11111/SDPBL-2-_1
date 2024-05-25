#pragma once
#include<Siv3D.hpp>
#include "BaseWindow.h"

class WindowKasoku : public BaseWindow {
public:
	//コンストラクタ
	WindowKasoku(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
	:BaseWindow(windowPos, windowSize, batuSize, startTime)
	{
		moveKind = MoveKind::Kasoku;
	}
	
	//行動(ここに広告の動きを記述してもらう)
	void act()override {
	if (a < 600) {
		a += 0.5;
	}

		m_vel = { 1+a,0 };
		if (m_window.x > 800) {
			m_window.x = -m_window.w;
			m_batu.x = m_window.x+m_window.w-m_batu.w;
		}
	}
	
private:
	//変数とかを宣言するときはここ
	double a=0;
	
};

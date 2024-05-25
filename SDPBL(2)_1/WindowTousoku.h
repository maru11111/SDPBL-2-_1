#pragma once
#include<Siv3D.hpp>
#include "BaseWindow.h"

class WindowTousoku: public BaseWindow {
public:
	//コンストラクタ
	WindowTousoku(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
		: BaseWindow(windowPos, windowSize, batuSize, startTime)
	{
		moveKind = MoveKind::BatuMove;
	}
	
//星の動きを書く
	//行動(ここに広告の動きを記述してもらう)
	void act()override {
		m_vel = { 200,0 };
		if (m_window.x > 800) {
			m_window.x = -m_window.w;
			m_batu.pos = m_window.pos + Vec2(m_window.w - m_batu.w, 0);
		}

	}

private:
	//変数とかを宣言するときはここ
	
};

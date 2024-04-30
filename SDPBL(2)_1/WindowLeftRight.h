#pragma once
#include "BaseWindow.h"

class WindowLeftRight :public BaseWindow {
public:
	//コンストラクタ
	WindowLeftRight(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime) {
		m_window = RectF{ windowPos,windowSize };
		m_batu = RectF{ windowPos + Vec2(windowSize.x - batuSize,0),batuSize };
		m_startTime = startTime;
	}

	//行動
	void act() override {
		//初期設定
		if (m_flag == false) {
			m_flagS = 0;
			speed = 100;
			m_flag = true;
		}

		//動き
		if (m_window.x < 0 || m_flagS == 1) {
			m_vel = { speed,0 };
			m_flagS = 1;
		}
		if (Scene::Size().x < m_window.x + m_window.w || m_flagS == 0) {
			m_vel = { -speed,0 };
			m_flagS = 0;
		}
	}
private:
	double speed;
};

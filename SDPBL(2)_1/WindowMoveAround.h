#pragma once
#include "BaseWindow.h"

class WindowMoveAround : public BaseWindow {
public:
	//コンストラクタ
	WindowMoveAround(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime) {
		m_window = RectF{ windowPos,windowSize };
		m_batu = RectF{ windowPos + Vec2(windowSize.x - batuSize,0),batuSize };
		m_startTime = startTime;
	}

	//行動
	void act() override {
		//初期設定
		if (m_flag == false) {
			speed = 200;
			m_vel = { 0,speed };
			m_flagS = 3;
			m_flag = true;
		}

		//動き
		//右に動く
		if (Scene::Size().y - 50 < m_window.y + m_window.h || m_flagS == 0) {
			//広告の位置を修正
			m_window.y = Scene::Size().y - 50 - m_window.h;
			m_batu.y = Scene::Size().y - 50 - m_window.h;
			//速度を与える
			m_vel = { speed,0 };
			//if分を継続させるためのフラグを設定
			m_flagS = 0;
		}

		//上に動く
		if (Scene::Size().x - 50 < m_window.x + m_window.w || m_flagS == 1) {
			m_window.x = Scene::Size().x - 50 - m_window.w;
			m_batu.x = m_window.x + m_window.w - m_batu.w;
			m_vel = { 0,-speed };
			m_flagS = 1;
		}

		//左に動く
		if (m_window.y < 0 + 50 || m_flagS == 2) {
			m_window.y = 50;
			m_batu.y = 50;
			m_vel = { -speed,0 };
			m_flagS = 2;
		}

		//下に動く
		if (m_window.x < 0 + 50 || m_flagS == 3) {
			m_window.x = 50;
			m_batu.x = m_window.x + m_window.w - m_batu.w;
			m_vel = { 0,speed };
			m_flagS = 3;
		}

	}
private:
	double speed;
};

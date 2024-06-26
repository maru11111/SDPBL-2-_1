﻿#pragma once
#include "BaseWindow.h"

/*ウィンドウの端から少し離れたところに沿って、反時計回りに移動する行動*/

class WindowMoveAround : public BaseWindow {
public:
	//コンストラクタ
	WindowMoveAround(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
		 : BaseWindow(windowPos, windowSize, batuSize, startTime)
	{
		moveKind = MoveKind::MoveAround;
	}


	//行動
	void act() override {
		//初期設定(一度だけ実行される)
		if (m_flag == false) {
			//始めに動く方向を m_flagS=3、つまり下に設定する。0なら右、1なら上、2なら左になる。
			m_flagS = 3;
			//速さ
			speed = 200;
			m_flag = true;
		}

		//動き
		//右に動く
		if (Scene::Size().y - 50 < m_window.y + m_window.h || m_flagS == 0) {
			//広告の位置を修正
			m_window.y = Scene::Size().y - 50 - m_window.h;
			m_batu.y = Scene::Size().y - 50 - m_window.h;
			//x方向の速度をspeed(speedが正の場合、右に動く)に設定する
			m_vel = { speed,0 };
			//if分を継続させるためのフラグを設定
			m_flagS = 0;
		}

		//上に動く
		if (Scene::Size().x - 50 < m_window.x + m_window.w || m_flagS == 1) {
			m_window.x = Scene::Size().x - 50 - m_window.w;
			m_batu.x = m_window.x + m_window.w - m_batu.w;
			//y方向の速度を-speed(speedが正の場合、上に動く)に設定する
			m_vel = { 0,-speed };
			m_flagS = 1;
		}

		//左に動く
		if (m_window.y < 0 + 50 || m_flagS == 2) {
			m_window.y = 50;
			m_batu.y = 50;
			//x方向の速度を-speed(speedが正の場合、左に動く)に設定する
			m_vel = { -speed,0 };
			m_flagS = 2;
		}

		//下に動く
		if (m_window.x < 0 + 50 || m_flagS == 3) {
			m_window.x = 50;
			m_batu.x = m_window.x + m_window.w - m_batu.w;
			//y方向の速度をspeed(speedが正の場合、下に動く)に設定する
			m_vel = { 0,speed };
			m_flagS = 3;
		}

	}
private:
	double speed=0;
};

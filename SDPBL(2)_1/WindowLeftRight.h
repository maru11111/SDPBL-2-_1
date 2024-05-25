#pragma once
#include "BaseWindow.h"

/*画面の左端から右端までを交互に移動する行動*/

class WindowLeftRight :public BaseWindow {
public:
	//コンストラクタ
	WindowLeftRight(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
		: BaseWindow(windowPos, windowSize, batuSize, startTime)
	{
		moveKind = MoveKind::LeftRight;
	}

	//行動
	void act() override {
		//初期設定(一度だけ実行される)
		if (m_flag == false) {
			//始めに動く方向を m_flagS=0、つまり左に設定する。m_flagS=1にすれば右になる。
			m_flagS = 0;
			//速さ
			speed = 100;
			m_flag = true;
		}

		//動き
		 //ウィンドウの左端についたら右に動く
		if (m_window.x < 0 || m_flagS == 1) {
			//x方向の速度をspeed(speedが正の場合、右に動く)にする
			m_vel = { speed,0 };
			//右に動いている最中であることを表すフラグ
			m_flagS = 1;
		}
		//ウィンドウの右端についたら左に動く
		if (Scene::Size().x < m_window.x + m_window.w || m_flagS == 0) {
			//x方向の速度を-speed(speedが正の場合、左に動く)にする
			m_vel = { -speed,0 };
			//左に動いている最中であることを表すフラグ
			m_flagS = 0;
		}
	}
private:
	double speed=0;
};

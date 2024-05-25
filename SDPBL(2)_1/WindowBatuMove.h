#pragma once
#include<Siv3D.hpp>
#include "BaseWindow.h"
#include<time.h>

class WindowBatuMove : public BaseWindow {
public:

	//コンストラクタ
	WindowBatuMove(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
		: BaseWindow(windowPos, windowSize, batuSize, startTime)
	{
		moveKind = MoveKind::BatuMove;
	}
	
	//バツを動かす関数
	void move(double dt) {
		m_batu.pos += vel_batu * dt;
	}

	//行動(ここに広告の動きを記述してもらう)
	void act()override {
		
		//初期設定(一度だけ実行される)
		if (m_flag == false) {
			//始めに動く方向を m_flagS=3、つまり下に設定する。0なら右、1なら上、2なら左になる。
			m_flagS = 3;
			//最初に少しだけバツを動かすためのベクトル{ 1, 1 }
			vel_batu = { 1, 1 };
			//速さ
			speed = 50;
			m_flag = true;
		}

		//バツの座標が広告の右下に来るまで下に動く
		if ( (m_batu.y <= m_window.y + m_window.h - m_batu.h) && (m_batu.x > m_window.x + m_window.w - m_batu.w) ) {
			vel_batu = { 0, speed };
		}

		//バツの座標が広告の左下に来るまで左に動く
		if ( (m_batu.y > m_window.y + m_window.h - m_batu.h) && (m_batu.x >= m_window.x + m_batu.w) ) {
			vel_batu = { -speed, 0 };
		}

		//バツの座標が広告の左上に来るまで上に動く
		if ( (m_batu.y >= m_window.y + m_batu.h) && (m_batu.x < m_window.x) ) {
			vel_batu = { 0, -speed };
		}

		//バツの座標が広告の右上に来るまで右に動く
		if ( (m_batu.y < m_window.y) && (m_batu.x <= m_window.x + m_window.w - m_batu.w) ) {
			vel_batu = { speed, 0 };
		}


	}

private:
	//変数とかを宣言するときはここ
	double speed;
	//バツの速さ
	Vec2 vel_batu = { 0,0 };
};

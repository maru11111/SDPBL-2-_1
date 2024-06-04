#pragma once
#include<Siv3D.hpp>
#include "BaseWindow.h"

class WindowHansya : public BaseWindow {
public:
	//コンストラクタ
	WindowHansya(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
	:BaseWindow(windowPos, windowSize, batuSize, startTime)
	{
		moveKind = MoveKind::Hansya;
	}

	//行動(ここに広告の動きを記述してもらう)
	void act()override {
		m_vel = { xspeed, yspeed };
		// 天井にぶつかったら 
		if (((m_window.y< 0) && (yspeed < 0))
			|| ((Scene::Size().y-50 < m_window.y) && (0 < yspeed)))
		{
			// ボールの速度の Y 成分の符号を反転する
			yspeed *= -1;
		}

		// 左右の壁にぶつかったら | If the ball hits the left or right wall
		if (((m_window.x < 0) && (xspeed < 0))
			|| ((Scene::Size().x -50 < m_window.x) && (0 < xspeed)))
		{
			// ボールの速度の X 成分の符号を反転する | Reverse the sign of the X component of the ball's velocity
			xspeed *= -1;
		}
	}

private:
	//変数とかを宣言するときはここ
	double xspeed = 100;
	double yspeed = -100;

};

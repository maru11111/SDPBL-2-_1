#pragma once
#include<Siv3D.hpp>
#include "BaseWindow.h"

class WindowXXX : public BaseWindow {
public:
	//コンストラクタ
	WindowXXX(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime) {
		m_window = RectF{ windowPos,windowSize };
		m_batu = RectF{ windowPos + Vec2(windowSize.x - batuSize,0),batuSize };
		m_startTime = startTime;

	}
	
	//行動(ここに広告の動きを記述してもらう)
	void act()override {
		/*円*/
		//t += 1;
		//x = -a*Cos(t*Math::Pi/180);
		//y = -a*Sin(t * Math::Pi / 180);
		//m_vel = {x,y};
		////////////////////////////////
		//double t = 0;
		//double x = 0, y = 0;
		//double a = 100;

		/*ハート*/
		//わからん

		///*定期的に不透明*/
		//t = watch.sF();
		//if ( (int)t % 5 == 0 ) {
		//	m_opacity += 0.05;
		//}
		//else {
		//	m_opacity -= 0.01;
		//}

		//if (1 <= m_opacity) {
		//	m_opacity = 1;
		//}
		//if (m_opacity <= 0) {
		//	m_opacity = 0;
		//}
		//////////////////////
		//watch.start();
		//double t = 0;
		//Stopwatch watch;

		/*下から出てくる*/
		//t = (int)watch.sF() % 13;

		//if (t < 2) {
		//	m_vel.y = -20;
		//}
		//else if (t < 6) {
		//	m_vel.y = 0;
		//}
		//else if(t < 8) {
		//	m_vel.y = 20;
		//}
		//else {
		//	m_vel.y = 0;
		//}
		//////////////////////////
		//Stopwatch watch;
		//int t;
		//watch.start();

	}

private:
	//変数とかを宣言するときはここ

};

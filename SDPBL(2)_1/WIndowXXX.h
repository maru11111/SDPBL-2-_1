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
		
	}

private:
	//変数とかを宣言するときはここ
	
};

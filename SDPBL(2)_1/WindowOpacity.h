#pragma once
#include<Siv3D.hpp>
#include "BaseWindow.h"

class WindowOpacity : public BaseWindow {
public:
	// コンストラクタ
	WindowOpacity(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
	:BaseWindow(windowPos, windowSize, batuSize, startTime) {
		moveKind = MoveKind::Opacity;  //広告の動きの種類を設定
		m_opacity = 1.0;  // 初期不透明度を設定
		fadingOut = true;  // 初期状態は透明度が減少
		lastUpdateTime = m_time.sF();  // 初期化時に現在の時間を設定
		isVisible = true;  // 初期状態は表示
	}

	// 行動(広告の動きを記述)
	void act() override {
		m_vel = { 100, 0 };
		double currentTime = m_time.sF();
		double deltaTime = currentTime - lastUpdateTime;

		updateOpacity(deltaTime);

		lastUpdateTime = currentTime;  // 更新後に時間を設定

		//画面から200px離れたら左から再び登場
		if (Scene::Width() + 200 < m_window.x) {
			//広告を画面の左端へ移動
			m_window.x = -m_window.w;
			//バツの位置を広告の左上にする
			m_batu.x = m_window.x + m_window.w - m_batu.w;
		}

	}

	// 透明度を徐々に更新するメソッド
	void updateOpacity(double deltaTime) {
		const double fadeSpeed = 0.7;  // 透明度の変化速度
		if (fadingOut) {
			m_opacity -= fadeSpeed * deltaTime;
			if (m_opacity <= 0.0) {
				m_opacity = 0.0;
				fadingOut = false;  // 透明度を増加させる
			}
		}
		else {
			m_opacity += fadeSpeed * deltaTime;
			if (m_opacity >= 1.0) {
				m_opacity = 1.0;
				fadingOut = true;  // 透明度を減少させる
			}
		}


	}

private:
	double lastUpdateTime;  // 最後に透明度を更新した時間
	bool isVisible;  // 表示状態
	bool fadingOut;  // 現在が減少フェーズかどうか
};

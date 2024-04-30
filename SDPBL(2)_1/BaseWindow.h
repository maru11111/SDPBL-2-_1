#pragma once
class BaseWindow {
public:
	//コンストラクタ
	BaseWindow() {
	}

	//ストップウォッチを開始する
	static void timeStart() {
		m_time.start();
	}

	//仮想関数
	virtual void act() = 0;

	//右を向いているか
	void isRight() {
		if (0 <= m_vel.x)m_right = true;
		else m_right = false;
	}
	void isDown() {
		if (0 <= m_vel.y)m_down = true;
		else m_right = false;
	}

	//広告を動かす関数
	void move(double dt) {
		m_window.pos += m_vel * dt;
		m_batu.pos += m_vel * dt;
	}

	//広告がクリックされたかどうか
	void isClick() {
		if (m_batu.leftClicked()) {
			m_beClick = true;
		}
		else {
			m_beClick = false;
		}
	}

	//広告がクリックされたかどうかを返す
	bool getIsClick() {
		return m_beClick;
	}

	//更新
	void update(double dt) {
		ClearPrint();
		if (m_startTime < m_time.sF()) {
			act();
			isClick();
			move(dt);
		}
		Print << m_time;
	}

	//描画
	void draw() {
		if (m_startTime < m_time.sF()) {
			m_window.draw();
			m_batu.draw(Palette::Red);
		}
	}
protected:
	//広告の図形
	RectF m_window, m_batu;
	//広告の速度
	Vec2 m_vel = { 0,0 };
	//広告がクリックされたかどうか
	bool m_beClick = false;
	//経過時間
	static Stopwatch m_time;
	//開始時間
	double m_startTime;
	//初期設定用フラグ
	bool m_flag = false;
	//右に進んでいるかどうか
	bool m_right = false;
	//下に進んでいるかどうか
	bool m_down = false;
	//スイッチ
	int m_flagS = 0;
};
Stopwatch BaseWindow::m_time;

#pragma once
class BaseWindow {
public:
	//コンストラクタ
	BaseWindow() {
	}

	enum class AdKind{
		Anna,
		Azarashi,
		Building,
		Car,
		MatchingApp,
		BatuDarake,
		Christmas,
		Hair,
		QuickCatch
	};

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

	//バツ印がクリックされたかどうか
	void isClick() {
		if (m_batu.leftClicked()) {
			m_beClick = true;
		}
		else {
			m_beClick = false;
		}
	}

	//広告がクリックされたかどうか
	void isClickAd() {
		if (m_window.leftClicked()) {
			m_beClickAd = true;
		}
		else {
			m_beClickAd = false;
		}
	}

	//広告がクリックされたかどうかを返す
	bool getIsClick() {
		return m_beClick;
	}

	//広告を踏んでしまった時の動作
	void actAdClick() {

	}

	////拡大した時のバツ印のずれを修正する関数
	//void setBatuPos() {
	//	if (m_size != 1) {
	//		m_batu = RectF{ (m_window.pos + Vec2(m_window.w * m_size - m_batu.w * m_size*m_size , -m_batu.w*m_size)) ,m_batu.w};
	//	}
	//}

	//更新
	void update(double dt) {
		ClearPrint();
		if (m_startTime < m_time.sF()) {
			isClick();
			act();
			move(dt);
			//setBatuPos();
		}
		Print << m_time;
	}

	
	//描画
	void draw() {
		debug.scaled(0.742).drawAt(800/2,600/2+98);
		if (m_startTime < m_time.sF()) {
			switch (kind) {
			case AdKind::Christmas:
				m_window.scaled(m_size)(v).draw(ColorF{ 1,1,1,m_opacity });
				break;
			case AdKind::Anna:
				m_window.scaled(m_size).draw(ColorF{ 1,1,1,m_opacity });
				break;
			default:
				break;
			}
			m_batu.scaled(m_size).draw(ColorF{1,0,0,m_opacity});
		}
	}
protected:
	//広告の図形
	RectF m_window, m_batu;
	//広告の速度
	Vec2 m_vel = { 0,0 };
	//広告のサイズ
	double m_size =1 ;
	//広告の不透明度
	double m_opacity = 1;
	//バツ印がクリックされたかどうか
	bool m_beClick = false;
	//広告がクリックされたかどうか
	bool m_beClickAd = false;
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
	//広告の種類
	AdKind kind = (AdKind)Random(0,1);
	//画像ファイル
	Texture s{ U"setagayacampus_05.jpg" };
	VideoTexture v{ U"SDPBL(2).mp4" };
	Texture debug{ U"image/haikei.png" };
};
Stopwatch BaseWindow::m_time;

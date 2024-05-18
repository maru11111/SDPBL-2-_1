#pragma once
class BaseWindow {
public:
	//コンストラクタ
	BaseWindow(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime);

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
	static void timeStart();
	//ストップウォッチを停止する
	static void timeStop();

	//仮想関数
	virtual void act() = 0;

	//広告を動かす関数
	void move(double dt);

	//バツ印がクリックされたかどうか判定
	void isClick();

	
	//広告がクリックされたかどうか判定
	void isClickAd();

	//バツがクリックされたかどうかを返す
	bool getIsClicked();

	//広告本体がクリックされたかどうかを返す
	bool getIsClickedAd();

	//m_AllBatuNotClickedを渡す
	static bool getIsNotAllClicked();

	//m_AllBatuNotClickedをセット
	static void SetNotAllClicked();

	//広告を踏んでしまった時の動作
	void actAdClick();

	//更新
	void update(double dt);

	//描画
	void draw();

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
	//インスタンス内でバツ印がクリックされたものがないかどうか
	static bool m_AllBatuNotClicked;
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

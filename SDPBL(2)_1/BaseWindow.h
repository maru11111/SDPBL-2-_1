#pragma once
#include "Common.h"

class BaseWindow {
public:
	//コンストラクタ
	BaseWindow(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime);

	//ストップウォッチを開始する
	static void timeStart();
	//ストップウォッチを停止する
	static void timeStop();
	//ストップウォッチをリセット
	static void timeReset();

	//仮想関数
	virtual void act() = 0;

	//広告を動かす関数
	virtual void move(double dt);

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

	//ポップする広告を設定
	void setPopKind();

	//更新
	void update(double dt);

	//描画
	void draw();

	//ポップする広告の描画
	static void drawPop(double dt);

	//getkindPop
	static AdKind getKindPop();

	//広告の動きを取得
	MoveKind getMoveKind();

	//広告が出現してからの経過時間を取得
	double getTime();


	//FlagFleqを更新
	void flagFreqT();
	//FlagFleqを取得
	bool getFlagFreq();

protected:
	//広告の図形
	RectF m_window, m_batu;
	//広告の速度
	Vec2 m_vel = { 0,0 };
	//広告のサイズ
	double m_size = 1;
	//広告の不透明度
	double m_opacity = 1;
	//バツ印がクリックされたかどうか
	bool m_beClick = false;
	//インスタンス内でバツ印がクリックされたものがないかどうか
	static bool m_AllBatuNotClicked;
	//広告がクリックされたかどうか
	bool m_beClickAd = false;
	//経過時間
	static Stopwatch m_timeS;
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
	AdKind kind = (AdKind)Random(1,8);
	//踏んでしまった広告の種類
	static AdKind kindPop;
	//踏んでしまった広告の不透明度
	static double m_opacityP;
	//動きの種類
	MoveKind moveKind;
	//オブジェクトごとの経過時間
	Stopwatch m_time;
	//オブジェクトの頻度増加フラグ
	bool flagFreq=false;
	//タイマー開始フラグ
	bool flagTimer=false;

	//画像ファイル
	Texture s{ U"setagayacampus_05.jpg" };
	VideoTexture v{ U"SDPBL(2).mp4" };
	VideoTexture christmas{ U"image/christmas.mp4" };
	Texture debug{ U"image/haikei.png" };

};

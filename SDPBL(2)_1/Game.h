#pragma once
#include "Common.h"
#include "WindowLeftRight.h"
#include "WindowMoveAround.h"
#include "WindowXXX.h"

enum class MoveKind {
	LeftRight,
	MoveAround,
};

class Game : public App::Scene
{
public:
	Game(const InitData& init);
	void update() override;
	void draw() const override;
	void add(MoveKind k, int time);

private:
	//ユニークポインタの配列を作成
	Array<std::unique_ptr<BaseWindow>>windows;
	//開始演出が終わったかどうか
	bool flagStart = false;
	//ゲーム開始時の処理をするためのフラグ
	bool flagS = false;
	//カウントダウン開始時の処理をするためのフラグ
	bool flagC = false;
	//開始演出の時間
	Stopwatch stopwatch;
	//背景サイズ
	double scale = 0.5;
	//スタート位置
	Vec2 fromP = { Scene::Size().x / 2, Scene::Size().y / 2 };
	Vec2 fromS = { 0.5,0 };
	//ゴール位置
	Vec2 toP = { Scene::Size().x / 2,Scene::Size().y / 2 + 98 };
	Vec2 toS = { 0.742,0 };
	// 移動の割合 0.0～1.0
	double t;
	// イージング関数を適用
	double e;
	// スタート位置からゴール位置へ e の割合だけ進んだ位置
	Vec2 pos = fromP;
	//移動終了フラグ
	bool flagDoneMove = false;;
	//ゲームオーバーフラグ
	bool flagEnd = false;
	//動きの種類
	MoveKind KindM;
	//出現するタイミング(DS用)
	int time = 0;
	//バツがクリックされていないかどうか
	bool batuNotClicked = true;



};

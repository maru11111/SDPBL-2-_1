#include "stdafx.h"
#include "Game.h"

Game::Game(const InitData& init)
	: IScene{init}
{
	//要素を入れる
	//windows << std::make_unique<追加したい要素のクラス名>(Vec2{初期のx座標,初期のy座標},Vec2{初期の幅,初期の高さ},初期のバツ印の一片の長さ,何秒後に出現するか);
	windows << std::make_unique<WindowLeftRight>(Vec2{ 100, 100 }, Vec2{ 100, 100 }, 10,5);
	windows << std::make_unique<WindowMoveAround>(Vec2{ 400, 400 }, Vec2{ 50, 50 }, 10,0);
	//windows << std::make_unique<WindowMoveAround>(Vec2{ 400, 400 }, Vec2{ 50, 50 }, 10, 30);
	//windows << std::make_unique<WindowXXX>(Vec2{ 20, 20 }, Vec2{ 200, 200 }, 10, 0);
	//windows << std::make_unique<WindowXXX>(Vec2{ 120, 20 }, Vec2{ 200, 200 }, 10, 3);
	//windows << std::make_unique<WindowXXX>(Vec2{ 220, 20 }, Vec2{ 200, 200 }, 10, 6);
	stopwatch.start();
}

void Game::update() {

	if (flagDoneMove == false) {
		Print << pos;
		// 移動の割合 0.0～1.0
		t = Min(stopwatch.sF() * 0.5, 1.0);

		// イージング関数を適用
		e = EaseInOutExpo(t);

		// スタート位置からゴール位置へ e の割合だけ進んだ位置
		pos = fromP.lerp(toP, e);
		scale = fromS.lerp(toS, e).x;
	}

	if (t == 1) {
		flagDoneMove = true;

		if (flagC == false) {
			stopwatch.restart();
			flagC = true;
		}
	}

	if (4 < stopwatch.sF()) {
		flagStart = true;
		BaseWindow::timeStart();
	}

	//ウィンドウ更新
	for (const auto& w : windows) {
		w->update(Scene::DeltaTime());
	}
	//要素の削除&メモリの解放
	windows.remove_if([](const auto& w) {return w->getIsClick(); });
}

void Game::draw() const {


	
	//通常
	//拡大
	//scaled(0.742).drawAt(Scene::Size().x/2,Scene::Size().y/2+98);
	//TextureAsset(U"BackGround").scaled(0.742).drawAt(Scene::Size().x / 2, Scene::Size().y / 2 + 98);
	TextureAsset(U"BackGround").scaled(scale).drawAt(pos);

	if (flagStart == false && flagDoneMove) {
	
		if (stopwatch.sF() < 1) {
			FontAsset(U"CountDown")(U"３").drawAt(Scene::Size() / 2,ColorF{0,0,0});
		}
		else if(stopwatch.sF() < 2) {
			FontAsset(U"CountDown")(U"２").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
		}
		else if (stopwatch.sF() < 3) {
			FontAsset(U"CountDown")(U"１").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
		}
		else if (stopwatch.sF() < 4) {
			FontAsset(U"CountDown")(U"スタート！").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
		}
		else {
			
		}
	}

	if (flagStart) {
		for (const auto& w : windows) {
			w->draw();
		}
	}
}

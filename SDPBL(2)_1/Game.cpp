#include "Game.h"

Game::Game(const InitData& init)
	: IScene{ init }
{
	switch (getData().mode) {
	case 1:
		//Normal

		break;
	case 2:
		//Hard

		break;
	case 3:
		//DataScience

		const Array<MoveKind> options =
		{
			MoveKind::LeftRight,
			MoveKind::MoveAround,
		};

		// 選択肢に対応する確率分布
		// （LeftRight は MoveAround よりも 2 倍出やすい）
		DiscreteDistribution distribution(
		{
			2,
			1,
		});

		for (int i = 0; i < 10; i++) {
			KindM = DiscreteSample(options, distribution);
			time = 0 + i * 3;
			add(KindM, time);
		}
		break;
	}

	//要素を入れる
	//windows << std::make_unique<追加したい要素のクラス名>(Vec2{初期のx座標,初期のy座標},Vec2{初期の幅,初期の高さ},初期のバツ印の一片の長さ,何秒後に出現するか);
	//windows << std::make_unique<WindowLeftRight>(Vec2{ 100, 100 }, Vec2{ 150, 100 }, 50,5);
	//windows << std::make_unique<WindowMoveAround>(Vec2{ 400, 400 }, Vec2{ 200, 150 }, 50,0);
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

	if (4.1 < stopwatch.sF()) {
		flagStart = true;
		BaseWindow::timeStart();
	}

	if (3.3 < stopwatch.sF() && !flagEnd) {
		AudioAsset(U"PlayBGM").play();
	}

	//ウィンドウ更新
	if (!flagEnd) {
		//trueになおす
		BaseWindow::SetNotAllClicked();
		for (const auto& w : windows) {
			//更新
			w->update(Scene::DeltaTime());

			//ゲームオーバー判定
			if (w->getIsClickedAd()) {
				flagEnd = true;
			}
		}
		//ゲームオーバー判定(後できれいにしたい...)
		if (BaseWindow::getIsNotAllClicked() == false) {
			flagEnd = false;
		}

	}

	//ゲームオーバー時処理
	if (flagEnd) {
		AudioAsset(U"PlayBGM").stop();
		BaseWindow::timeStop();

	}

	//要素の削除&メモリの解放
	windows.remove_if([](const auto& w) {return w->getIsClicked(); });
}

void Game::add(MoveKind k, int time) {
	switch (k) {
	case MoveKind::LeftRight:
		windows << std::make_unique<WindowLeftRight>(Vec2{ 400, 400 }, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::MoveAround:
		windows << std::make_unique<WindowMoveAround>(Vec2{ 400, 400 }, Vec2{ 200, 150 }, 50, time);
		break;
	}
}

void Game::draw() const {

	TextureAsset(U"BackGround").scaled(scale).drawAt(pos);

	if (flagStart == false && flagDoneMove) {
		if (stopwatch.sF() < 1) {
			AudioAsset(U"CountDown").play();
		}
		if (0.1 < stopwatch.sF()) {
			if (stopwatch.sF() < 1.1) {
				FontAsset(U"CountDown")(U"３").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
			}
			else if (stopwatch.sF() < 2.1) {
				FontAsset(U"CountDown")(U"２").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
			}
			else if (stopwatch.sF() < 3.1) {
				FontAsset(U"CountDown")(U"１").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
			}
			else if (stopwatch.sF() < 4.1) {
				FontAsset(U"CountDown")(U"スタート！").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
			}
			else {

			}
		}
	}


	if (flagStart) {
		for (const auto& w : windows) {
			w->draw();
		}
	}
}

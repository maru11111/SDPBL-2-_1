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

		for (int i = 0; i < numAd; i++) {
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

Game::~Game() {
	BaseWindow::timeReset();
}

void Game::update() {
	ClearPrint();

	if (flagDoneMove == false) {
		//Print << pos;
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

	if (3.3 < stopwatch.sF() && !flagEnd && !flagClear) {
		AudioAsset(U"PlayBGM").setVolume(0.7).play();
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
		if (flagHit == false) {
			AudioAsset(U"Hit").setVolume(0.8).play();
			flagHit = true;
			stopwatch.restart();
			fromP = rect.pos;
			toP = rect.pos + Vec2(-rect.w, 0);
		}
		if (2 < stopwatch.sF()) {
			if (flagSkip == false) {
				stopwatchSkip.start();
				AudioAsset(U"GameOver").play();
				flagSkip = true;
			}

			// 移動の割合 0.0～1.0
			t = Min(stopwatchSkip.sF() * 0.5, 1.0);

			// イージング関数を適用
			e = EaseOutCubic(t);

			// スタート位置からゴール位置へ e の割合だけ進んだ位置
			rect.pos = fromP.lerp(toP, e);
		}
		if (8< stopwatch.sF()) {

			if (rect.leftClicked()) {
				changeScene(State::Title);
			}
		}
	}

	for (auto& w : windows) {
		if (w->getIsClicked()){
		// 削除数をカウント
			numClickAd++;
		//バツをクリックしたときの音
			if (numClickAd != numAd) {
				AudioAsset(U"BatuClick").setVolume(0.5).play();
			}
			else {
				AudioAsset(U"BatuClickLast").setVolume(0.5).play();
			}
	}

	}
	//要素の削除&メモリの解放
	windows.remove_if([](const auto& w) {return w->getIsClicked(); });

	//クリア時
	if (numClickAd == numAd) {
		if (flagHit == false) {
			AudioAsset(U"PlayBGM").stop();
			stopwatch.restart();
			flagClear = true;
			fromS = Scene::Center() + Vec2(0, -200 - FontAsset(U"Clear").fontSize());
			toS = Scene::Center() + Vec2(0, -100);
			fromP = rect.pos;
			toP = rect.pos + Vec2(-rect.w, 0);
			flagHit = true;
		}

		if (1.5 < stopwatch.sF()) {
			if (!flag1) {
				AudioAsset(U"Clear").play();
				flag1 = true;
			}
			opacityG += 0.8 * Scene::DeltaTime();

			// 移動の割合 0.0～1.0
			t = Min((stopwatch.sF() - 1.5) * 0.34, 1.0);

			// イージング関数を適用
			e = EaseOutCubic(t);

			// スタート位置からゴール位置へ e の割合だけ進んだ位置
			posFontGameOver = fromS.lerp(toS, e);

			// 移動の割合 0.0～1.0
			t = Min((stopwatch.sF() - 3.5) * 0.34, 1.0);

			// イージング関数を適用
			e = EaseOutCubic(t);

			// スタート位置からゴール位置へ e の割合だけ進んだ位置
			rect.pos = fromP.lerp(toP, e);

			if (rect.leftClicked()) {
				changeScene(State::Title);
			}
		}
	}
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

	//Print << flagStart;
	if (flagStart) {
		for (const auto& w : windows) {
			w->draw();
		}
	}

	//ゲームオーバー時
	if (flagEnd&&flagHit) {
		if (2 < stopwatch.sF()) {
			BaseWindow::drawPop(Scene::DeltaTime());
			if (BaseWindow::getKindPop() == AdKind::Christmas) {
				christmas.advance();
				christmas.scaled(0.405).drawAt(Scene::Center() + Vec2(0, 34), ColorF(1, 1, 1,1));
			}


		}
		if (stopwatch.sF() < 8) {
			rect.draw(ColorF(0, 0, 0, 0.5));
			FontAsset(U"Skip")(U"GaveOver ",8-(int)stopwatch.sF()).drawAt(rect.x + rect.w / 2, rect.y + rect.h / 2);
		}else{
			rect.draw(ColorF(0, 0, 0, 0.5));
			FontAsset(U"Skip")(U"タイトルへ▶|").drawAt(rect.x+rect.w/2, rect.y+rect.h/2);
		}
	}
	//クリア時
	if (numClickAd == numAd) {
		if (1.5 < stopwatch.sF()) {
			FontAsset(U"Clear")(U"クリア").drawAt(posFontGameOver, ColorF(0, 0, 0, opacityG));
			rect.draw(ColorF(0, 0, 0, 0.5));
			FontAsset(U"Skip")(U"タイトルへ▶|").drawAt(rect.x + rect.w / 2, rect.y + rect.h / 2);
		}
	}

	FontAsset(U"Num")(U"💥: ",numClickAd, U"/",numAd).draw(10,10,ColorF(0,0,0));
}

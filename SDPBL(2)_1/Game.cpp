#include "Game.h"

Game::Game(const InitData& init)
	: IScene{ init },
	resourcePath(Resource(U"video/christmas.mp4")),
	temporaryFilePath(FileSystem::TemporaryDirectoryPath() + U"MyApp/christmas.mp4"),
	christmas(LoadVideoFromResource(resourcePath, temporaryFilePath, Loop::Yes))
{

	switch (getData().mode) {
	case Mode::Normal:
		//Normal
		//windows << std::make_unique<WindowOpacity>(Vec2{ 100, 100 }, Vec2{ 150, 100 }, 50, 0);
		add(MoveKind::LeftRight, 0);
		add(MoveKind::MoveAround,5);
		add(MoveKind::Tousoku,10);
		add(MoveKind::Opacity,15);
		add(MoveKind::BatuMove,20);
		add(MoveKind::LeftRight,25);
		add(MoveKind::MoveAround,30);
		add(MoveKind::Tousoku,35);
		add(MoveKind::Opacity,40);
		add(MoveKind::BatuMove,45);
		add(MoveKind::LeftRight, 50);
		add(MoveKind::MoveAround, 55);
		add(MoveKind::Tousoku, 60);
		add(MoveKind::Opacity, 65);
		add(MoveKind::BatuMove, 70);

		break;
	case Mode::Hard:
		//Hard
		add(MoveKind::Tousoku, 0);
		add(MoveKind::Circle, 1.5);
		add(MoveKind::Kasoku, 3);
		add(MoveKind::Circle, 4.5);
		add(MoveKind::Opacity, 6);
		add(MoveKind::Circle, 7.5);
		add(MoveKind::Hansya, 9);
		add(MoveKind::Circle, 10.5);
		add(MoveKind::Tousoku, 12);
		add(MoveKind::Hansya, 13.5);
		add(MoveKind::Kasoku, 15);
		add(MoveKind::Hansya, 16.5);
		add(MoveKind::Opacity, 18);
		add(MoveKind::Hansya, 19.5);
		add(MoveKind::Circle, 21);

		break;
	case Mode::DS:
		//DataScience

		const Array<MoveKind> options =
		{
			MoveKind::LeftRight,
			MoveKind::MoveAround,
			MoveKind::Opacity,
			MoveKind::Kasoku,
			MoveKind::Circle,
			MoveKind::BatuMove,
			MoveKind::Tousoku,
			MoveKind::Hansya,
		};

		// 選択肢に対応する確率分布
		DiscreteDistribution distribution(
		{
			getData().numFreq[(int)MoveKind::LeftRight],
			getData().numFreq[(int)MoveKind::MoveAround],
			getData().numFreq[(int)MoveKind::Opacity],
			getData().numFreq[(int)MoveKind::Kasoku],
			getData().numFreq[(int)MoveKind::Circle],
			getData().numFreq[(int)MoveKind::BatuMove],
			getData().numFreq[(int)MoveKind::Tousoku],
			getData().numFreq[(int)MoveKind::Hansya],
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
	getData().saveNumFreq();
}

void Game::update() {

	ClearPrint();
	//for (int i = 0; i < (int)MoveKind::Num; i++) {
	//	Print << getData().numFreq[i];
	//}

	//Print << stopwatch.sF();

	//Print << (int)getData().mode;

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

	if (4.3 < stopwatch.sF()) {
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
			//出現確率更新
			//もし6秒以上消されていなかったら
			if (6 < w->getTime()&& !w->getFlagFreq()) {
				//頻度を上げる
				getData().numFreq[(int)w->getMoveKind()] += 0.25;
				//一つのオブジェクトで一度だけ更新
				w->flagFreqT();
			}
			//もし1秒以内に消されていたら
			if (w->getIsClicked() && w->getTime() < 2) {
				//頻度が1より大きいか
				if ( 1<(int)w->getMoveKind() ) {
					//頻度を下げる
					getData().numFreq[(int)w->getMoveKind()] -= 0.25;
				}
			}

			//ゲームオーバー判定
			if (w->getIsClickedAd()) {
				flagEnd = true;
				//クリックしてしまった広告の動きを取得
				ClickMoveKind = w->getMoveKind();
			}
		}
		//ゲームオーバー判定(後できれいにしたい...)
		//もしバツを消していればゲームオーバーを撤回
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
			//踏んでしまった広告の出る頻度を上げる
			getData().numFreq[(int)ClickMoveKind] += 0.5;
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
		windows << std::make_unique<WindowLeftRight>(Vec2{ RandomVec2(Rect{0, 0, Scene::Width()-200, Scene::Height()-150}) }, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::MoveAround:
		windows << std::make_unique<WindowMoveAround>(Vec2{ RandomVec2(Rect{0,0,Scene::Width() - 200, Scene::Height() - 150}) }, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Opacity:
		windows << std::make_unique<WindowOpacity>(Vec2{ RandomVec2(Rect{0,0,Scene::Width() - 200, Scene::Height() - 150} )}, Vec2{200, 150}, 50, time);
		break;
	case MoveKind::Kasoku:
		windows << std::make_unique<WindowKasoku>(Vec2{ RandomVec2(Rect{0, 0, Scene::Width() - 200, Scene::Height() - 150}) }, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Circle:
		windows << std::make_unique<WindowCircle>(Vec2{ RandomVec2(Rect{0, 0, Scene::Width() - 200 -150, Scene::Height() - 150 -200}) }, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::BatuMove:
		windows << std::make_unique<WindowBatuMove>(Vec2{ RandomVec2(Rect{0, 0, Scene::Width() - 200, Scene::Height() - 150}) }, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Tousoku:
		windows << std::make_unique<WindowTousoku>(Vec2{ RandomVec2(Rect{0, 0, Scene::Width() - 200, Scene::Height() - 150}) }, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Hansya:
		windows << std::make_unique<WindowHansya>(Vec2{ RandomVec2(Rect{0, 0, Scene::Width() - 200, Scene::Height() - 150}) }, Vec2{ 200, 150 }, 50, time);
		break;
	}
}

void Game::add(MoveKind k, double x, double y, double time) {
	switch (k) {
	case MoveKind::LeftRight:
		windows << std::make_unique<WindowLeftRight>(Vec2{x,y}, Vec2{200, 150}, 50, time);
		break;
	case MoveKind::MoveAround:
		windows << std::make_unique<WindowMoveAround>(Vec2{x,y}, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Opacity:
		windows << std::make_unique<WindowOpacity>(Vec2{x,y}, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Kasoku:
		windows << std::make_unique<WindowKasoku>(Vec2{x,y}, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Circle:
		windows << std::make_unique<WindowCircle>(Vec2{ x,y}, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::BatuMove:
		windows << std::make_unique<WindowBatuMove>(Vec2{ x,y}, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Tousoku:
		windows << std::make_unique<WindowTousoku>(Vec2{x,y}, Vec2{ 200, 150 }, 50, time);
		break;
	case MoveKind::Hansya:
		windows << std::make_unique<WindowHansya>(Vec2{x,y}, Vec2{ 200, 150 }, 50, time);
		break;
	}
}

void Game::draw() const {

	TextureAsset(U"BackGround").scaled(scale).drawAt(pos);

	if (flagStart == false && flagDoneMove) {
		if ( 0 < stopwatch.sF()) {
			
			AudioAsset(U"CountDown").play();
		}
		if (0.3 < stopwatch.sF()) {
			if (stopwatch.sF() < 1.3) {
				FontAsset(U"CountDown")(U"３").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
			}
			else if (stopwatch.sF() < 2.3) {
				FontAsset(U"CountDown")(U"２").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
			}
			else if (stopwatch.sF() < 3.3) {
				FontAsset(U"CountDown")(U"１").drawAt(Scene::Size() / 2, ColorF{ 0,0,0 });
			}
			else if (stopwatch.sF() < 4.3) {
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
			FontAsset(U"Skip")(U"GameOver ",8-(int)stopwatch.sF()).drawAt(rect.x + rect.w / 2, rect.y + rect.h / 2);
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

	FontAsset(U"Num")(U"撃破数: ",numClickAd, U"/",numAd).draw(10,10,ColorF(0,0,0));
}

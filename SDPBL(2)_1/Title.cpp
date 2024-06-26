﻿#include "Title.h"

Title::Title(const InitData& init)
	:IScene{ init }
{
	for (int i = 0; i < 3; i++) {
		button << RectF{ 25 + 275 * i, Scene::Center().y + 100,200,120 };
	}
	
}

Title::~Title() {
	AudioAsset(U"TitleBGM").stop();
}

void Title::update() {

	//ゲームシーンへ移動
	//if (KeyEnter.down()) {
	//	changeScene(State::Game, 0.5s);
	//}

	AudioAsset(U"TitleBGM").play();


	if (button[0].leftClicked()) {
		AudioAsset(U"Click").play();
		getData().mode = Mode::Normal;
		changeScene(State::Game,0);
	}
	if (button[1].leftClicked()) {
		AudioAsset(U"Click").play();
		getData().mode = Mode::Hard;
		changeScene(State::Game,0);
	}
	if (button[2].leftClicked()) {
		AudioAsset(U"Click").play();
		getData().mode = Mode::DS;
		changeScene(State::Game,0);
	}
}

void Title::draw()const {
	TextureAsset(U"BackGround").scaled(0.5).drawAt(Scene::Size().x / 2, Scene::Size().y / 2);
	Rect{ 0,0,Scene::Width(),Scene::Height() }.draw(ColorF(0.2, 0.2, 0.2, 0.5));

	//FontAsset(U"Title")(U"広告を消すゲーム(仮)").drawAt(Scene::Center().x, Scene::Center().y - 150);
	TextureAsset(U"Title").scaled(0.5).drawAt(Scene::Center().x, Scene::Center().y+25);

	/*for (auto& b : button) {
		if (b.mouseOver()) {
			b.rounded(30).drawFrame(10,ColorF(1,0,0)).draw();
		}
		else {
			b.rounded(30).draw();
		}
	}*/

	if (button[0].mouseOver()) {
		button[0].rounded(30).drawFrame(15, Palette::Seagreen).draw(Palette::Mediumseagreen);
	}
	else {
		button[0].rounded(30).drawFrame(10, Palette::Seagreen).draw(Palette::Mediumseagreen);
	}

	if (button[1].mouseOver()) {
		button[1].rounded(30).drawFrame(15, Palette::Darkred).draw(Palette::Firebrick);
	}
	else {
		button[1].rounded(30).drawFrame(10, Palette::Darkred).draw(Palette::Firebrick);
	}

	if (button[2].mouseOver()) {
		button[2].rounded(30).drawFrame(15, Palette::Darkmagenta).draw(Palette::Darkorchid);
	}
	else {
		button[2].rounded(30).drawFrame(10, Palette::Darkmagenta).draw(Palette::Darkorchid);
	}

	FontAsset(U"Stage")(U"ノーマル").drawAt( button[0].x+button[0].w/2 , button[0].y + button[0].h/2, ColorF(0,0,0));
	FontAsset(U"Stage")(U"ハード").drawAt(button[1].x + button[1].w / 2, button[1].y + button[1].h / 2, ColorF(0, 0, 0));
	FontAsset(U"StageDS")(U"データ\nサイエンス").drawAt(button[2].x + button[2].w / 2, button[2].y + button[2].h / 2, ColorF(0, 0, 0));

	//DSリセット
	if (SimpleGUI::Button(U"DS確率リセットボタン", Vec2{ Scene::Width()-260, 10}))
	{
		getData().dataReset();
	}
}

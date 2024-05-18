#include "Title.h"

Title::Title(const InitData& init)
	:IScene{ init }
{
	for (int i = 0; i < 3; i++) {
		button << RectF{ 50 + 275 * i, Scene::Center().y,140,120 };

	}

}

void Title::update() {

	if (KeyEnter.down()) {
		changeScene(State::Game, 0.5s);
	}
}

void Title::draw()const {
	TextureAsset(U"BackGround").scaled(0.5).drawAt(Scene::Size().x / 2, Scene::Size().y / 2);
	Rect{ 0,0,Scene::Width(),Scene::Height() }.draw(ColorF(0.2, 0.2, 0.2, 0.5));

	FontAsset(U"Title")(U"広告を消すゲーム(仮)").drawAt(Scene::Center().x, Scene::Center().y - 150);

	for (auto& b : button) {
		if (b.leftClicked()) { Print << 0; };
		Print << b.x;
		b.draw();
	}



}

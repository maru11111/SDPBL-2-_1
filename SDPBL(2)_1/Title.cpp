#include "stdafx.h"
#include "Title.h"

Title::Title(const InitData& init)
	:IScene{init}
{
	
}

void Title::update() {
	if (KeyEnter.down()) {
		changeScene(State::Game,0s);
	}
}

void Title::draw()const {
	TextureAsset(U"BackGround").scaled(0.5).drawAt(Scene::Size().x / 2, Scene::Size().y / 2);;
}

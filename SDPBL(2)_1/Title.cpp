#include "stdafx.h"
#include "Title.h"

Title::Title(const InitData& init)
	:IScene{init}
{
	
}

void Title::update() {
	if (KeyEnter.down()) {
		changeScene(State::Game,0);
	}
}

void Title::draw()const {

}

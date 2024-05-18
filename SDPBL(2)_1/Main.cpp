# include "Common.h"
# include "Title.h"
# include "Game.h"

void Main()
{

	TextureAsset::Register(U"BackGround", U"image/haikei.png");

	FontAsset::Register(U"CountDown", 100, U"font/keifont.ttf");
	FontAsset::Register(U"Title", 75, U"font/keifont.ttf");

	AudioAsset::Register(U"CountDown", U"audio/ピッピッピー.wav");
	AudioAsset::Register(U"PlayBGM", U"audio/大慌て.mp3",Loop::Yes);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);

	//ゲームシーンからスタート
	//manager.init(State::Game);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}

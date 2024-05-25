# include "Common.h"
# include "Title.h"
# include "Game.h"

void Main()
{

	TextureAsset::Register(U"BackGround", U"image/haikei.png");
	TextureAsset::Register(U"Anna", U"image/SDPBL広告.png");
	TextureAsset::Register(U"Azarashi", U"image/azarashi.png");
	TextureAsset::Register(U"BatuDarake", U"image/batu.png");
	TextureAsset::Register(U"Building", U"image/building.png");
	TextureAsset::Register(U"Car", U"image/car.png");
	//TextureAsset::Register(U"Christmas", U"image/christmas.mp4");
	TextureAsset::Register(U"Hair", U"image/hair.jpg");
	TextureAsset::Register(U"MatchingApp", U"image/matching.png");
	TextureAsset::Register(U"QuickCatch", U"image/quick.png");
	TextureAsset::Register(U"Title", U"image/title7.png");

	FontAsset::Register(U"CountDown", 100, U"font/keifont.ttf");
	FontAsset::Register(U"Title", 75, U"font/keifont.ttf");
	FontAsset::Register(U"Skip", 50, U"font/keifont.ttf");
	FontAsset::Register(U"GameOver", 100, U"font/keifont.ttf");
	FontAsset::Register(U"Num",50, U"font/keifont.ttf");
	FontAsset::Register(U"Clear", 100, U"font/keifont.ttf");
	FontAsset::Register(U"Stage", 50, U"font/keifont.ttf");
	FontAsset::Register(U"StageDS", 40, U"font/keifont.ttf");

	AudioAsset::Register(U"CountDown", U"audio/ピッピッピー.wav");
	AudioAsset::Register(U"PlayBGM", U"audio/大慌て.mp3", Loop::Yes);
	AudioAsset::Register(U"Hit", U"audio/damage.mp3");
	AudioAsset::Register(U"GameOver", U"audio/GameOver.wav");
	AudioAsset::Register(U"BatuClick", U"audio/8bit獲得1.mp3");
	AudioAsset::Register(U"BatuClickLast", U"audio/8bit獲得6.mp3");
	AudioAsset::Register(U"Clear", U"audio/ジャジャーン3.mp3");

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

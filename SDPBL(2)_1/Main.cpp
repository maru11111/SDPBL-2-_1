# include "Common.h"
# include "Title.h"
# include "Game.h"

void Main()
{
	TextureAsset::Register(U"BackGround", Resource(U"image/haikei.png"));
	TextureAsset::Register(U"Anna", Resource(U"image/SDPBL広告.png"));
	TextureAsset::Register(U"Azarashi", Resource(U"image/azarashi.png"));
	TextureAsset::Register(U"BatuDarake", Resource(U"image/batu.png"));
	TextureAsset::Register(U"Building", Resource(U"image/building.png"));
	TextureAsset::Register(U"Car", Resource(U"image/car.png"));
	//VIdeoTextureAssetがないためそれぞれのクラスが動画ファイルを持ってます
	//VideoTextureAsset::Register(U"Christmas", Resource(U"image/christmas.mp4"));
	TextureAsset::Register(U"Hair", Resource(U"image/hair.jpg"));
	TextureAsset::Register(U"MatchingApp", Resource(U"image/matching.png"));
	TextureAsset::Register(U"QuickCatch", Resource(U"image/quick.png"));
	TextureAsset::Register(U"Title", Resource(U"image/title7.png"));

	FontAsset::Register(U"CountDown", 100, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Title", 75, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Skip", 50, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"GameOver", 100, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Num",50, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Clear", 100, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Stage", 50, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"StageDS", 40, Resource(U"font/keifont.ttf"));

	AudioAsset::Register(U"CountDown", Resource(U"audio/ピッピッピー.wav"));
	AudioAsset::Register(U"PlayBGM", Resource(U"audio/大慌て.mp3"), Loop::Yes);
	AudioAsset::Register(U"Hit", Resource(U"audio/damage.mp3"));
	AudioAsset::Register(U"GameOver", Resource(U"audio/GameOver.wav"));
	AudioAsset::Register(U"BatuClick", Resource(U"audio/8bit獲得1.mp3"));
	AudioAsset::Register(U"BatuClickLast", Resource(U"audio/8bit獲得6.mp3"));
	AudioAsset::Register(U"Clear", Resource(U"audio/ジャジャーン3.mp3"));

	//ウィンドウタイトルを変更
	Window::SetTitle(U"広告のバツを押すゲーム");

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

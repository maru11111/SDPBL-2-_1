# include "Common.h"
# include "Title.h"
# include "Game.h"

void Main()
{
	TextureAsset::Register(U"BackGround", Resource(U"image/haikei.png"));
	TextureAsset::Register(U"Anna", Resource(U"image/anna.png"));
	TextureAsset::Register(U"Azarashi", Resource(U"image/azarashi.png"));
	TextureAsset::Register(U"BatuDarake", Resource(U"image/batu.png"));
	TextureAsset::Register(U"Building", Resource(U"image/building.png"));
	TextureAsset::Register(U"Car", Resource(U"image/car.png"));
	//VIdeoTextureAssetがないためそれぞれのクラスが動画ファイルを持ってます...
	//VideoTextureAsset::Register(U"Christmas", Resource(U"image/christmas.mp4"));
	TextureAsset::Register(U"Hair", Resource(U"image/hair.jpg"));
	TextureAsset::Register(U"MatchingApp", Resource(U"image/matching.png"));
	TextureAsset::Register(U"QuickCatch", Resource(U"image/quick.png"));
	TextureAsset::Register(U"Title", Resource(U"image/title7.png"));
	TextureAsset::Register(U"Batu", Resource(U"image/redBatu.png"));

	FontAsset::Register(U"CountDown", 100, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Title", 75, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Skip", 50, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"GameOver", 100, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Num",50, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Clear", 100, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"Stage", 50, Resource(U"font/keifont.ttf"));
	FontAsset::Register(U"StageDS", 40, Resource(U"font/keifont.ttf"));
	AudioAsset::Register(U"CountDown", Resource(U"audio/ピッピッピー.wav"));
	AudioAsset::Register(U"PlayBGM", Resource(U"audio/maou_bgm_8bit09.mp3"), Loop::Yes);
	AudioAsset::Register(U"TitleBGM", Resource(U"audio/maou_bgm_8bit29.mp3"), Loop::Yes);
	AudioAsset::Register(U"EndBGM", Resource(U"audio/maou_bgm_8bit20.mp3"), Loop::Yes);
	AudioAsset::Register(U"Hit", Resource(U"audio/damage.mp3"));
	AudioAsset::Register(U"GameOver", Resource(U"audio/GameOver.wav"));
	AudioAsset::Register(U"BatuClick", Resource(U"audio/8bit獲得1.mp3"));
	AudioAsset::Register(U"BatuClickLast", Resource(U"audio/8bit獲得6.mp3"));
	AudioAsset::Register(U"Click", Resource(U"audio/8bit選択2.mp3"));
	AudioAsset::Register(U"Clear", Resource(U"audio/ジャジャーン3.mp3"));

	// 非同期ロードを開始
	TextureAsset::LoadAsync(U"BackGround");
	TextureAsset::LoadAsync(U"Anna");
	TextureAsset::LoadAsync(U"Azarashi");
	TextureAsset::LoadAsync(U"BatuDarake");
	TextureAsset::LoadAsync(U"Building");
	TextureAsset::LoadAsync(U"Car");
	TextureAsset::LoadAsync(U"Hair");
	TextureAsset::LoadAsync(U"MatchingApp");
	TextureAsset::LoadAsync(U"QuickCatch");
	TextureAsset::LoadAsync(U"Title");
	TextureAsset::LoadAsync(U"Batu");

	FontAsset::LoadAsync(U"CountDown");
	FontAsset::LoadAsync(U"Title");
	FontAsset::LoadAsync(U"Skip");
	FontAsset::LoadAsync(U"GameOver");
	FontAsset::LoadAsync(U"Num");
	FontAsset::LoadAsync(U"Clear");
	FontAsset::LoadAsync(U"Stage");
	FontAsset::LoadAsync(U"StageDS");

	AudioAsset::LoadAsync(U"CountDown");
	AudioAsset::LoadAsync(U"TitleBGM");
	AudioAsset::LoadAsync(U"PlayBGM");
	AudioAsset::LoadAsync(U"EndBGM");
	AudioAsset::LoadAsync(U"Hit");
	AudioAsset::LoadAsync(U"GameOver");
	AudioAsset::LoadAsync(U"BatuClick");
	AudioAsset::LoadAsync(U"BatuClickLast");
	AudioAsset::LoadAsync(U"Click");
	AudioAsset::LoadAsync(U"Clear");

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

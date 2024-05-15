# include <Siv3D.hpp>
#include "WindowLeftRight.h"
#include "WindowMoveAround.h"
#include "WindowXXX.h"

void Main()
{
	//ユニークポインタの配列を作成
	Array<std::unique_ptr<BaseWindow>>windows;

	//要素を入れる
	/*
	windows << std::make_unique<追加したい要素のクラス名>(Vec2{初期のx座標,初期のy座標},Vec2{初期の幅,初期の高さ},初期のバツ印の一片の長さ,何秒後に出現するか);
	*/
	windows << std::make_unique<WindowLeftRight>(Vec2{ 100, 100 }, Vec2{ 100, 100 }, 10,5);
	windows << std::make_unique<WindowMoveAround>(Vec2{ 400, 400 }, Vec2{ 50, 50 }, 10,0);
	//windows << std::make_unique<WindowMoveAround>(Vec2{ 400, 400 }, Vec2{ 50, 50 }, 10, 30);
	//windows << std::make_unique<WindowXXX>(Vec2{ 20, 20 }, Vec2{ 200, 200 }, 10, 0);
	//windows << std::make_unique<WindowXXX>(Vec2{ 120, 20 }, Vec2{ 200, 200 }, 10, 3);
	//windows << std::make_unique<WindowXXX>(Vec2{ 220, 20 }, Vec2{ 200, 200 }, 10, 6);

	//タイマーを開始
	BaseWindow::timeStart();

	while (System::Update())
	{
		//更新
		for (const auto& w : windows) {
			w->update(Scene::DeltaTime());
		}
		//要素の削除&メモリの解放
		windows.remove_if([](const auto& w) {return w->getIsClick(); });

		//描画
		for (const auto& w : windows) {
			w->draw();
		}
	}
}

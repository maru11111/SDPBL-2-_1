#pragma once
#include "Common.h"
#include "WindowLeftRight.h"
#include "WindowMoveAround.h"
#include "WindowXXX.h"

class Game : public App::Scene
{
public:
	Game(const InitData& init);
	void update() override;
	void draw() const override;

private:
	//ユニークポインタの配列を作成
	Array<std::unique_ptr<BaseWindow>>windows;
};


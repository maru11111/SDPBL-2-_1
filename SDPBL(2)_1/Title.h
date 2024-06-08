#pragma once

#include "Common.h"

class Title :public App::Scene
{
public:
	Title(const InitData& init);
	~Title();
	void update() override;
	void draw() const override;

private:
	Array<RectF>button;
};

# pragma once
# include <Siv3D.hpp>

// シーンの名前
enum class State
{
	Title,
	Game,
};

// 共有するデータ
struct GameData
{
	int mode = 3;
};

using App = SceneManager<State, GameData>;

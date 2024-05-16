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
};

using App = SceneManager<State, GameData>;

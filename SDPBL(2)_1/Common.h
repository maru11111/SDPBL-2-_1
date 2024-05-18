# pragma once
# include <Siv3D.hpp>

// シーンの名前
enum class State
{
	Title,
	Game,
};

enum class AdKind {
	Anna,
	Azarashi,
	BatuDarake,
	Building,
	Car,
	Christmas,
	Hair,
	MatchingApp,
	QuickCatch
};

// 共有するデータ
struct GameData
{
	int mode = 3;
};

using App = SceneManager<State, GameData>;

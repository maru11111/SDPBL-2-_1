# pragma once
# include <Siv3D.hpp>

// シーンの名前
enum class State
{
	Title,
	Game,
};


enum class MoveKind {
	LeftRight,
	MoveAround,
	Opacity,
	Kasoku,
	Circle,
	BatuMove,
	Tousoku,
	Hansya,
	Num,
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
	//広告の動きのでやすさ
	double numFreq[(int)MoveKind::Num];


	//データ読み込み
	GameData(){
		JSON json = JSON::Load(U"data/data.json");
		//for (int i = 0; i < (int)MoveKind::Num;i++) {
		//	
		//}

		if (not json) // もし読み込みに失敗したら
		{
			throw Error{ U"Failed to load `config.json`" };
		}

		numFreq[(int)MoveKind::LeftRight] = json[U"LeftRight"].get<double>();
		numFreq[(int)MoveKind::MoveAround] = json[U"MoveAround"].get<double>();
		numFreq[(int)MoveKind::Opacity] = json[U"Opacity"].get<double>();
		numFreq[(int)MoveKind::Kasoku] = json[U"Kasoku"].get<double>();
		numFreq[(int)MoveKind::Circle] = json[U"Circle"].get<double>();
		numFreq[(int)MoveKind::BatuMove] = json[U"BatuMove"].get<double>();
		numFreq[(int)MoveKind::Tousoku] = json[U"Tousoku"].get<double>();
		numFreq[(int)MoveKind::Hansya] = json[U"Hansya"].get<double>();
	}

	void saveNumFreq() {
		JSON json;

		json[U"LeftRight"] = numFreq[(int)MoveKind::LeftRight];
		json[U"MoveAround"] = numFreq[(int)MoveKind::MoveAround];
		json[U"Opacity"] = numFreq[(int)MoveKind::Opacity];
		json[U"Kasoku"] = numFreq[(int)MoveKind::Kasoku];
		json[U"Circle"] = numFreq[(int)MoveKind::Circle];
		json[U"BatuMove"] = numFreq[(int)MoveKind::BatuMove];
		json[U"Tousoku"] = numFreq[(int)MoveKind::Tousoku];
		json[U"Hansya"] = numFreq[(int)MoveKind::Hansya];

		json.save(U"data/data.json");
	}

	void dataReset() {
		numFreq[(int)MoveKind::LeftRight] = 1.0;
		numFreq[(int)MoveKind::MoveAround] = 1.0;
		numFreq[(int)MoveKind::Opacity] = 1.0;
		numFreq[(int)MoveKind::Kasoku] = 1.0;
		numFreq[(int)MoveKind::Circle] = 1, 0;
		numFreq[(int)MoveKind::BatuMove] = 1.0;
		numFreq[(int)MoveKind::Tousoku] = 1.0;
		numFreq[(int)MoveKind::Hansya] = 1.0;

		saveNumFreq();
	}
};

using App = SceneManager<State, GameData>;

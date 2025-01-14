#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <map>

namespace GameManger {
	enum StageRooms {
		Shop = 1,
		Rest = 2,
		Buff = 3,
		Battle = 4  
	};

	class GameManger {
	public:
		static GameManger& GetInstance();

		//Character GenerateCharacter(std::string name);
		void GenerateBattleManager();

		StageRooms GenerateRandomRoom(const std::map<StageRooms, double>& roomProbabilities);
		std::vector<StageRooms> GenerateTwoRandomRooms(const std::map<StageRooms, double>& roomProbabilities);

		void VisitShop();
		void VisitRest();
		void VisiteBuffRoom();
		void BeginBattle();

		void BeginPlay();
		
		void SetStage(int num);
		int getCurrentStage();

	private:
		int stage;

		GameManger() = default;
		GameManger(const GameManger&) = delete;
		GameManger& operator=(const GameManger&) = delete;
		GameManger(GameManger&&) = delete;
		GameManger& operator=(GameManger&&) = delete;

		std::map<StageRooms, double> roomProbabilities = {
			{Shop, 20.0},
			{Rest, 10.0},
			{Buff, 10.0},
			{Battle, 60.0}
		};

		std::string StageRoomToString(StageRooms room) {
			switch (room) {
			case Shop: return "Shop";
			case Rest: return "Rest";
			case Buff: return "Buff";
			case Battle: return "Battle";
			default: return "Unknown";
			}
		};
	};

} // namespace GameManger

#endif // !GAMEMANAGER_H
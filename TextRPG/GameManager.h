#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
<<<<<<< HEAD
#include <vector>
#include <map>

=======
#include"BattleManager.h"
#include"Character.h"
>>>>>>> e1e55e7f8e65481cf3f2e5a58b12d10f56bb0252
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

		StageRooms GenerateRandomRoom(const std::map<StageRooms, double>& roomProbabilities);
		std::vector<StageRooms> GenerateTwoRandomRooms(const std::map<StageRooms, double>& roomProbabilities);

		void VisitShop();
		void VisitRest();
<<<<<<< HEAD
		void VisitBuffRoom();
		void BeginBattle();
=======
		void VisiteBuffRoom();
		void BeginBattle(Character* player,int stage);
>>>>>>> e1e55e7f8e65481cf3f2e5a58b12d10f56bb0252

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
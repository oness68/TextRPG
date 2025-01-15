#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <map>

#include"BattleManager.h"
#include"Character.h"
namespace GameManger {
	enum StageRooms {
		Shop = 1,
		Rest = 2,
		Buff = 3,
		Battle = 4  
	};

	enum BuffRooms {
		Dice = 1,
		Number = 2,
		Rand = 3,
		Game = 4
		// 아이템 랜덤 변경
	};

	class GameManger {
	public:
		static GameManger& GetInstance();

		/*
		StageRooms GenerateRandomRoom(const std::map<StageRooms, double>& roomProbabilities);
		std::vector<StageRooms> GenerateTwoRandomRooms(const std::map<StageRooms, double>& roomProbabilities);
		*/

		template <typename RoomType>
		RoomType GenerateRandomRoom(const std::map<RoomType, double>& roomProbabilities) {
			double totalProbability = 0.0;

			std::srand(static_cast<unsigned>(std::time(nullptr)));

			for (const auto& room : roomProbabilities) {
				totalProbability += room.second;
			}

			double randomValue = (std::rand() % 10000) / 10000.0 * totalProbability;
			double cumulativeProbability = 0.0;

			for (const auto& room : roomProbabilities) {
				cumulativeProbability += room.second;
				if (randomValue <= cumulativeProbability) {
					return room.first;
				}
			}

			return roomProbabilities.begin()->first;
		}

		template <typename RoomType>
		std::vector<RoomType> GenerateTwoRandomRooms(const std::map<RoomType, double>& roomProbabilities, RoomType allowDuplicateRoom = RoomType()) {
			std::vector<RoomType> selectedRooms;

			RoomType firstRoom = GenerateRandomRoom(roomProbabilities);
			selectedRooms.push_back(firstRoom);

			RoomType secondRoom;
			do {
				secondRoom = GenerateRandomRoom(roomProbabilities);
			} while (secondRoom == firstRoom && allowDuplicateRoom != firstRoom);

			selectedRooms.push_back(secondRoom);

			return selectedRooms;
		};

		void VisitShop(Character* player);
		void VisitRest(Character* player);
		void VisitBuffRoom(Character* player);
		void BeginBattle(Character* player,int stage);

		void BeginPlay(Character* player);
		
		void SetStage(int num);
		int GetCurrentStage();

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
			case Shop: return "상점";
			case Rest: return "휴식";
			case Buff: return "그냥방";
			case Battle: return "전투";
			default: return "Unknown";
			}
		};

		std::map<BuffRooms, double> buffRoomProbabilities = {
			{Dice, 25.0},
			{Number, 25.0},
			{Rand, 25.0},
			{Game, 25.0},
		};

		std::string BuffRoomToString(BuffRooms room) {
			switch (room) {
			case Dice: return "주사위 굴리기";
			case Number: return "숫자 맞추기";
			case Game: return "미구현";
			case Rand: return "랜덤 스텟 조정";
			default: return "Unknown";
			}
		};
	};

} // namespace GameManger

#endif // !GAMEMANAGER_H
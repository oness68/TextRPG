#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <random>

#include "BattleManager.h"
#include "Character.h"
#include "Shop.h"
#include "Menu.h"

namespace GameManger {
	enum StageRooms {
		Market = 1,
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

		//template <typename RoomType>
		//RoomType GenerateRandomRoom(const std::map<RoomType, double>& roomProbabilities);

		//template <typename RoomType>
		//std::vector<RoomType> GenerateTwoRandomRooms(const std::map<RoomType, double>& roomProbabilities, std::optional<RoomType> allowDuplicateRoom = std::nullopt);

		template <typename RoomType>
		RoomType GenerateRandomRoom(const std::map<RoomType, double>& roomProbabilities) {
			double totalProbability = 0.0;

			// 로그 추가: 전체 확률의 합을 확인
			for (const auto& room : roomProbabilities) {
				totalProbability += room.second;
				std::cout << room.first << " (" << room.second << "), ";
			}

			random_device rd;
			mt19937 gen(rd());
			uniform_real_distribution<double> dist(0.0, totalProbability);

			double randomValue = dist(gen);
			double cumulativeProbability = 0.0;

			for (const auto& room : roomProbabilities) {
				cumulativeProbability += room.second;
				if (randomValue <= cumulativeProbability) {
					//std::cout << "Selected Room: " << room.first << std::endl;  // 선택된 방 로그
					return room.first;
				}
			}

			//std::cout << "Returning default room: " << roomProbabilities.begin()->first << std::endl;
			return roomProbabilities.begin()->first;  // default return
		}

		template <typename RoomType>
		std::vector<RoomType> GenerateTwoRandomRooms(const std::map<RoomType, double>& roomProbabilities, std::optional<RoomType> allowDuplicateRoom) {
			std::vector<RoomType> selectedRooms;

			// 첫 번째 방을 생성
			RoomType firstRoom = GenerateRandomRoom(roomProbabilities);
			selectedRooms.push_back(firstRoom);

			//std::cout << "First room selected: " << firstRoom << std::endl;

			RoomType secondRoom;
			do {
				secondRoom = GenerateRandomRoom(roomProbabilities);
				//std::cout << "Second room selected: " << secondRoom << std::endl;
			} while ((secondRoom == firstRoom) && !allowDuplicateRoom);

			selectedRooms.push_back(secondRoom);

			//std::cout << "Final Rooms Selected: ";
			for (const auto& room : selectedRooms) {
				std::cout << room << " ";
			}
			std::cout << std::endl;

			return selectedRooms;
		}

		void VisitShop(Character* player);
		void VisitRest(Character* player);
		void VisitBuffRoom(Character* player);
		void BeginBattle(Character* player,int stage);

		// 버프방 게임 목록
		void BuffDice(Character* player);
		void BuffNumber(Character* player);
		void BuffRand(Character* player);
		void BuffCoinToss(Character* player);

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
			{Market, 20.0},
			{Rest, 10.0},
			{Buff, 10.0},
			{Battle, 50.0}
		};

		std::string StageRoomToString(StageRooms room) {
			switch (room) {
			case Market: return "상점";
			case Rest: return "휴식";
			case Buff: return "?방";
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
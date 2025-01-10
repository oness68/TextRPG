#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>

namespace GameManger {

	class GameManger {
	public:
		static GameManger& GetInstance();

		//Character GenerateCharacter(std::string name);
		void GenerateBattleManager();

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
	};

} // namespace GameManger

#endif // !GAMEMANAGER_H
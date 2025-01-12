#pragma once

#include <string>

// юс╫ц
class Character {

};

namespace GameManger {

	class GameManger {
	public:
		static GameManger& GetInstance();

		Character GenerateCharacter();
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
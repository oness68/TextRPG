#include "GameManager.h"

namespace GameManger {

    // 싱글톤 인스턴스 반환
    GameManger& GameManger::GetInstance() 
    {
        static GameManger instance;
        return instance;
    }

    // 상점 방문 함수
    void GameManger::VisitShop() 
    {
        // TODO: 구현 필요
    }

    // 전투 시작 함수
    void GameManger::BeginBattle() 
    {
        // TODO: 구현 필요
    }

    // BattleManager 생성 함수
    void GameManger::GenerateBattleManager() 
    {
        // TODO: 구현 필요
    }

    // 휴식 장소 방문 함수
    void GameManger::VisitRest() 
    {
        // TODO: 구현 필요
    }

    // 버프룸 방문 함수
    void GameManger::VisiteBuffRoom() 
    {
        // TODO: 구현 필요
    }

    // 캐릭터 생성 함수
    Character GameManger::GenerateCharacter() 
    {
        // TODO: 구현 필요
        return Character();
    }

    // 현재 스테이지 반환 함수
    int GameManger::getCurrentStage() 
    {
        // TODO: 구현 필요
        return stage;
    }

    // 스테이지 단계 설정
    void GameManger::SetStage(int num)
    {
        // TODO: 구현 필요
    }

    // 게임시작
    void GameManger::BeginPlay()
    {
        // TODO: 구현 필요
    }
} // namespace GameManger
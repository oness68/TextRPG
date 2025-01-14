#include "GameManager.h"

#include <iostream>
using namespace std;

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

    // 휴식 장소 방문 함수
    void GameManger::VisitRest() 
    {
        // TODO: 구현 필요
    }

    // 버프룸 방문 함수
    void GameManger::VisitBuffRoom() 
    {
        // TODO: 구현 필요
    }

    // 캐릭터 생성 함수
    //Character GameManger::GenerateCharacter(string name)
    //{
    //    // TODO: 구현 필요
    //    return Character::Character(name);
    //}

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
        SetStage(1);

        std::srand(static_cast<unsigned>(std::time(nullptr)));
        std::vector<StageRooms> selectedRooms = GenerateTwoRandomRooms(roomProbabilities);

        cout << "Room: " << StageRoomToString(selectedRooms[0]) << endl;
        cout << "Room: " << StageRoomToString(selectedRooms[1]) << endl;


    }

    StageRooms GameManger::GenerateRandomRoom(const std::map<StageRooms, double>& roomProbabilities)
    {
        double totalProbability = 0.0;

        for (const auto& room : roomProbabilities) 
        {
            totalProbability += room.second;
        }

        double randomValue = (std::rand() % 10000) / 10000.0 * totalProbability; // std::rand()는 0부터 32767까지의 난수를 생성 0 ~ 9999 나머지
        double cumulativeProbability = 0.0;

        for (const auto& room : roomProbabilities) 
        {
            cumulativeProbability += room.second;
            if (randomValue <= cumulativeProbability) 
            {
                return room.first;
            }
        }

        return Shop;
    }

    // 배틀방만 중복이 가능하도록 처리한 랜덤 방 선택 함수
    std::vector<StageRooms> GameManger::GenerateTwoRandomRooms(const std::map<StageRooms, double>& roomProbabilities) 
    {
        std::vector<StageRooms> selectedRooms;

        StageRooms firstRoom = GenerateRandomRoom(roomProbabilities);
        selectedRooms.push_back(firstRoom);

        StageRooms secondRoom;
        do 
        {
            secondRoom = GenerateRandomRoom(roomProbabilities);
        } while (firstRoom != Battle && secondRoom == firstRoom);

        selectedRooms.push_back(secondRoom);

        return selectedRooms;
    }

} // namespace GameManger
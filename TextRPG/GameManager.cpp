#include "GameManager.h"
#include "Log.h"

#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

namespace GameManger {

    // 싱글톤 인스턴스 반환
    GameManger& GameManger::GetInstance() 
    {
        static GameManger instance;

        return instance;
    }

    // 상점 방문 함수
    void GameManger::VisitShop(Character* player)
    {
        int input;
        cout << "1. 구매" << endl;
        cout << "2. 판매" << endl;
        cout << "3. 강화" << endl;
        cout << "4. 인벤토리" << endl;
        cout << "5. 나가기" << endl;
        cin >> input;


    }

    // 전투 시작 함수
    void GameManger::BeginBattle(Character* player, int stage)
    {
        BattleManager* BM = BattleManager::GetInstance();

        BM->BeginBattle(player, stage);
        // TODO: 리턴 처리
    }

    // 휴식 장소 방문 함수
    void GameManger::VisitRest(Character* player)
    {
        int currentHP = player->GetCurrentHP();
        int maxHP = player->GetMaxHP();

        if (maxHP / 2 > currentHP)
        {
            player->SetCurrentHP(currentHP + (maxHP / 2));
        }
        else
        {
            player->SetCurrentHP(maxHP);
        }
    }

    // 버프룸 방문 함수
    void GameManger::VisitBuffRoom(Character* player)
    {
        // TODO: 구현 필요
    }

    // 현재 스테이지 반환 함수
    int GameManger::GetCurrentStage() 
    {
        return stage;
    }

    // 스테이지 단계 설정
    void GameManger::SetStage(int num)
    {
        stage = num;
    }

    // 게임시작
    void GameManger::BeginPlay(Character* player)
    {
        int stage = 1;

        player->DisplayStatus();

        Log* logger = Log::GetInstance();
        
        // logger->PrintLog("HI", 1);

        VisitShop(player);
        
        SetStage(stage);

        while (stage <= 20)
        {
            std::srand(static_cast<unsigned>(std::time(nullptr)));
            std::vector<StageRooms> selectedRooms = GenerateTwoRandomRooms(roomProbabilities);

            cout << "1. Room: " << StageRoomToString(selectedRooms[0]) << endl;
            cout << "2. Room: " << StageRoomToString(selectedRooms[1]) << endl;

            int choice;
            std::cout << "선택할 방 번호 (1 또는 2 입력): ";
            std::cin >> choice;

            if (choice == 1) {
                // 첫 번째 방에 대한 처리
                switch (selectedRooms[0]) {
                case Shop:
                    std::cout << "상점에 도착했습니다!" << std::endl;
                    VisitShop(player);
                    break;
                case Rest:
                    std::cout << "휴식을 취합니다." << std::endl;
                    VisitRest(player);
                    break;
                case Buff:
                    std::cout << "버프를 받았습니다!" << std::endl;
                    break;
                case Battle:
                    std::cout << "전투가 시작되었습니다!" << std::endl;
                    BeginBattle(player, stage);
                    break;
                default:
                    std::cout << "알 수 없는 방입니다." << std::endl;
                    break;
                }
            }
            else if (choice == 2) {
                // 두 번째 방에 대한 처리
                switch (selectedRooms[1]) {
                case Shop:
                    std::cout << "상점에 도착했습니다!" << std::endl;
                    break;
                case Rest:
                    std::cout << "휴식을 취합니다." << std::endl;
                    VisitRest(player);
                    break;
                case Buff:
                    std::cout << "버프를 받았습니다!" << std::endl;
                    break;
                case Battle:
                    std::cout << "전투가 시작되었습니다!" << std::endl;
                    BeginBattle(player, stage);
                    break;
                default:
                    std::cout << "알 수 없는 방입니다." << std::endl;
                    break;
                }
            }
            else {
                std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
            }

            SetStage(++stage);
        }
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
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
        Log::GetInstance()->PrintLog("상점에 방문했습니다!\n", (int)EShop, true);

        Shop shop;

        vector<string> menuItems = {
            "구매",
            "판매",
            "강화",
            "인벤토리",
            "나가기"
        };

        vector<function<void()>> actions = {
            [&]() {
                cout << "구매를 선택했습니다." << endl;
                shop.BuyItem(*player);
            },
            [&]() {
                cout << "판매를 선택했습니다." << endl;
                shop.SellItem(*player);
            },
            [&]() {
                cout << "강화를 선택했습니다." << endl;
                shop.UseEnchancer(*player);
            },
            [&]() {
                cout << "인벤토리를 확인합니다." << endl;
                player->DisplayInventory();
            },
            [&]() {
                cout << "상점을 떠납니다." << endl;
            }
        };

        Menu menuSystem(menuItems, actions);

        // 메뉴 실행
        while (true) {
            menuSystem.DisplayMenu((int)EShop, true);
            menuSystem.RunMenu((int)EShop, true);

            if (menuSystem.GetSelectedIndex() == 4) {
                break;
            }

            cout << endl; // 메뉴 간격 조정
        }
        /*
        while (true) {
            // 메뉴 출력
            cout << "1. 구매" << endl;
            cout << "2. 판매" << endl;
            cout << "3. 강화" << endl;
            cout << "4. 인벤토리" << endl;
            cout << "5. 나가기" << endl;
            cout << "선택: ";
            cin >> input;

            // 입력값 처리
            switch (input) {
            case 1:
                cout << "구매를 선택했습니다." << endl;
                shop.BuyItem(*player);
                // 구매 관련 로직 추가
                break;
            case 2:
                cout << "판매를 선택했습니다." << endl;
                shop.SellItem(*player);
                // 판매 관련 로직 추가
                break;
            case 3:
                cout << "강화를 선택했습니다." << endl;
                shop.UseEnchancer(*player);
                // 강화 관련 로직 추가
                break;
            case 4:
                cout << "인벤토리를 확인합니다." << endl;
                // 인벤토리 관련 로직 추가

                //player->GetInventory();
                player->DisplayInventory();

                break;
            case 5:
                cout << "프로그램을 종료합니다." << endl;
                return; // 반복문 종료
            default:
                cout << "잘못된 입력입니다. 다시 선택하세요." << endl;
                break;
            }

            cout << endl; // 메뉴 간격 조정
        }
        */
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
        auto buffRooms = GenerateTwoRandomRooms(buffRoomProbabilities, std::optional<BuffRooms>(BuffRooms::Dice));

        for (size_t i = 0; i < buffRooms.size(); ++i) {
            std::cout << i + 1 << ". Buff Room: " << BuffRoomToString(buffRooms[i]) << std::endl;
        }
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

        //player->DisplayStatus();

        Log* logger = Log::GetInstance();
        
        // VisitBuffRoom(player);

        VisitShop(player);

        SetStage(stage);
        BeginBattle(player, stage);
        SetStage(++stage);

        while (stage <= 20)
        {
            auto stageRooms = GenerateTwoRandomRooms(roomProbabilities, std::optional<StageRooms>(StageRooms::Battle));

            for (size_t i = 0; i < stageRooms.size(); ++i) {
                std::cout << i + 1 << ". Stage Room: " << StageRoomToString(stageRooms[i]) << std::endl;
            }

            int choice;
            std::cout << "선택할 방 번호 (1 또는 2 입력): ";
            std::cin >> choice;

            if (choice == 1 || choice == 2) {
                StageRooms selectedRoom = stageRooms[choice - 1];

                switch (selectedRoom) {
                case Market:
                    std::cout << "상점에 도착했습니다!" << std::endl;
                    VisitShop(player);
                    break;
                case Rest:
                    std::cout << "휴식을 취합니다." << std::endl;
                    VisitRest(player);
                    break;
                case Battle:
                    std::cout << "전투가 시작되었습니다!" << std::endl;
                    BeginBattle(player, stage);
                    break;
                default:
                    std::cout << "알 수 없는 방입니다." << std::endl;
                    VisitBuffRoom(player);
                    break;
                }
            }
            else {
                std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
                continue;
            }

            SetStage(++stage);
        }
    }

    template <typename RoomType>
    RoomType  GameManger::GenerateRandomRoom(const std::map<RoomType, double>& roomProbabilities) {
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
    std::vector<RoomType> GameManger::GenerateTwoRandomRooms(const std::map<RoomType, double>& roomProbabilities, std::optional<RoomType> allowDuplicateRoom) {
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

    /*
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
    */
    
    /*
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
    */
} // namespace GameManger
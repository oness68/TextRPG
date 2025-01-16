#include "Menu.h"

#include <iostream>
#include <conio.h>
#include <cstdlib> 

using namespace std;

Menu::Menu(const std::vector<std::string>& menuItems, const std::vector<std::function<void()>>& actions)
    : menuItems(menuItems), actions(actions), selectedIndex(0) {
}

void Menu::ShowMenu(int selectedIndex, int caseNumber, bool clear, string info) {
    Log::GetInstance()->PrintLog(info, caseNumber, clear);

    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedIndex) {
            cout << menuItems[i] << " <" << endl;
        }
        else {
            cout << menuItems[i] << endl;
        }
    }
}

void Menu::ShowMenu(int selectedIndex, int caseNumber, bool clear) {
    Log::GetInstance()->PrintLog("", caseNumber, clear);

    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedIndex) {
            cout << menuItems[i] << " <" << endl;
        }
        else {
            cout << menuItems[i] << endl;
        }
    }
}

void Menu::DisplayMenu(int caseNumber, bool clear, string info) {
    ShowMenu(selectedIndex, caseNumber, clear, info);  // 메뉴를 첫 번째 항목으로 표시
}

int Menu::GetSelectedIndex() {
    return selectedIndex;  // 현재 선택된 항목 인덱스 반환
}

void Menu::AddMenuItem(const std::string& item, const std::function<void()>& action) {
    menuItems.push_back(item);  // 메뉴 항목 추가
    actions.push_back(action);  // 해당 항목의 동작 추가
}

void Menu::RemoveMenuItem(int index) {
    if (index >= 0 && index < menuItems.size()) {
        menuItems.erase(menuItems.begin() + index);  // 특정 항목 제거
        actions.erase(actions.begin() + index);  // 동작도 함께 제거
    }
}

void Menu::RunMenu(int caseNumber, bool clear, string info) {
    char c;
    while (true) {
        if (_kbhit()) {  // 키 입력을 확인
            c = _getch();  // 키 입력 받기

            if (c == -32) {  // 방향키 입력
                c = _getch();  // 방향키의 실제 값 받기

                switch (c) {
                case UP:
                    // 위 방향키
                    selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();  // 상위 항목으로 이동
                    if (info != "")
                    {
                        ShowMenu(selectedIndex, caseNumber, clear, info);
                    }
                    else
                    {
                        ShowMenu(selectedIndex, caseNumber, clear);
                    }
                    break;
                case DOWN:
                    // 아래 방향키
                    selectedIndex = (selectedIndex + 1) % menuItems.size();  // 하위 항목으로 이동
                    if (info != "")
                    {
                        ShowMenu(selectedIndex, caseNumber, clear, info);
                    }
                    else
                    {
                        ShowMenu(selectedIndex, caseNumber, clear);
                    }
                    break;
                default:
                    break;
                }
            }
            else if (c == ENTER) {  // 엔터키 입력
                /*
                cout << "Selected Index: " << selectedIndex << endl;
                cout << "Executing Action: " << menuItems[selectedIndex] << endl;

                cout << "Menu Items and Actions:" << endl;
                for (size_t i = 0; i < menuItems.size(); ++i) {
                    cout << "  [" << i << "] " << menuItems[i];
                    if (i == selectedIndex) {
                        cout << " (Currently Selected)";
                    }
                    cout << endl;
                }

                cout << "Actions Array Details:" << endl;
                for (size_t i = 0; i < actions.size(); ++i) {
                    cout << "  Action[" << i << "]: ";
                    if (actions[i]) {
                        cout << "Valid Function" << endl;  // 유효한 함수가 존재하는 경우
                    }
                    else {
                        cout << "Empty/Null Function" << endl;  // 함수가 없는 경우
                    }
                }

                cout << "selectedIndex: " << selectedIndex << ", actions.size(): " << actions.size() << endl;
                */
                if (selectedIndex >= 0 && selectedIndex < actions.size()) {
                    // cout << "Executing action for index: " << selectedIndex << endl;
                    actions[selectedIndex]();  // 선택된 항목의 동작 실행
                }
                else {
                    cout << "Invalid selection!" << endl;  // 범위를 벗어난 경우 처리
                }

                // 메뉴 종료 후 반복문을 탈출
                break;
            }
            else if (c == ESC) {  // ESC 키 입력 시 프로그램 종료
                cout << "Exiting..." << endl;
                break;
            }
        }
    }
}

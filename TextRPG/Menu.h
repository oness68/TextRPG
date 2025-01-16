#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <functional>

#include "Log.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

class Menu {
public:
    Menu(const std::vector<std::string>& menuItems = {}, const std::vector<std::function<void()>>& actions = {});
    void DisplayMenu(int caseNumber, bool clear, string info);  // 메뉴 표시
    int GetSelectedIndex();  // 선택된 항목 인덱스 반환

    void AddMenuItem(const std::string& item, const std::function<void()>& action);  // 메뉴 항목 추가 (캡쳐된게 있을경우 힙에할당되어 std::function 소멸자에서 정리됨, 없을경우는 스텍에생성)
    // 참조 캡쳐도 사용가능
    void RemoveMenuItem(int index);  // 메뉴 항목 제거

    void RunMenu(int caseNumber, bool clear, string info);  // 메뉴를 실행하고 선택된 항목에 따라 처리
private:
    //void ShowMenu(int selectedIndex);  // 선택된 인덱스를 기준으로 메뉴 표시
    void ShowMenu(int selectedIndex, int caseNumber, bool clear, string info);
    void ShowMenu(int selectedIndex, int caseNumber, bool clear);

    std::vector<std::string> menuItems;  // 메뉴 항목 리스트
    std::vector<std::function<void()>> actions;  // 각 항목에 대한 동작 리스트
    int selectedIndex;  // 현재 선택된 인덱스
};

#endif
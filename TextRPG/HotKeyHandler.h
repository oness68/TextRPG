#pragma once
#include <iostream>
#include <windows.h>
#include <thread>
#include <format>
#include "Character.h"

void HotkeyHandler(Character& character) {
    while (true) {
        // Ctrl+0 입력 확인 (VK_CONTROL = 0x11, VK_0 = 0x30)
        if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x30) & 0x8000)) {
            character.DisplayStatus();
            Sleep(500); // 입력 지연 (반복 호출 방지)
        }

        // 프로그램 종료 키 (예: Ctrl+Q) 감지
        //if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x51) & 0x8000)) {
        //    std::cout << "Hotkey Handler 종료!" << std::endl;
        //    break;
        //}

        Sleep(100); // CPU 점유율 감소를 위한 대기
    }
}
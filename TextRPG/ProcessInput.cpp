#include <iostream>
#include <conio.h>
#include <chrono>

#include "ProcessInput.h"

namespace PI 
{
    bool isInputEnabled = true;
    bool isRunning = true;

    void ProcessInput() 
    {
        while (isRunning) {
            if (isInputEnabled && _kbhit()) 
            {
                char ch = _getch();
                //std::cout << "입력된 키: " << ch << std::endl;
            }
            else 
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

    void ClearInputBuffer() 
    {
        while (_kbhit()) {
            _getch(); // 버퍼에 쌓인 키를 모두 소비
        }
    }
}
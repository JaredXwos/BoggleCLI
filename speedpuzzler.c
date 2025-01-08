//
// Created by hatoa on 8/1/2025.
//
#include <stdio.h>
#include "speedpuzzler.h"
#ifdef _WIN32
#include <windows.h>
static void enableANSI() {
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

int speedpuzzler() {
#ifdef _WIN32
    enableANSI(); // Enable ANSI support on Windows
#endif
    printf("This quiz provides a limited preset board. Type all valid words findable on the board."
           "Press enter after every word.");
    return 0;
}

//
// Created by hatoa on 8/1/2025.
//

#ifndef SPEEDPUZZLER_H
#define SPEEDPUZZLER_H
struct board {
    const char king[17];
    const char **answer;
};
extern const struct board list[];
extern const int total_boards;
int speedpuzzler();
#endif //SPEEDPUZZLER_H

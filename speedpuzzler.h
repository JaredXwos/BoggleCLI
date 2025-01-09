//
// Created by hatoa on 8/1/2025.
//

#ifndef SPEEDPUZZLER_H
#define SPEEDPUZZLER_H
struct board {
    const char king[17];
    const char **answer;
};
extern const struct board ester_list[];
extern const struct board rates_list[];
extern const struct board least_list[];
extern const int ester_total;
extern const int rates_total;
extern const int least_total;
int speedPuzzler(const char* five);
#endif //SPEEDPUZZLER_H

#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

const int kPoints[10][6] = {
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
};

const int kBars[10][7] = {
    {1, 1, 1, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1},
};

const int kBarIndex[7][5] = {
    {-1, 0, 0, 0, -1},
    {1, -1, -1, -1, 2},
    {1, -1, -1, -1, 2},
    {-1, 3, 3, 3, -1},
    {4, -1, -1, -1, 5},
    {4, -1, -1, -1, 5},
    {-1, 6, 6, 6, -1},
};

void renderDigit(array<string, 7>& display, int colOffset, int digit) {
    for (int i = 0; i < 3; ++i) {
        display[3 * i][colOffset] = kPoints[digit][i] ? '+' : ' ';
        display[3 * i][colOffset + 4] = kPoints[digit][i + 3] ? '+' : ' ';
    }
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 5; ++col) {
            int bar = kBarIndex[row][col];
            if (bar == -1) {
                continue;
            }
            char segmentChar = bar % 3 == 0 ? '-' : '|';
            display[row][colOffset + col] = kBars[digit][bar] ? segmentChar : ' ';
        }
    }
}

array<string, 7> renderTime(int hour, int minute) {
    array<string, 7> display;
    display.fill(string(29, ' '));
    display[2][14] = 'o';
    display[4][14] = 'o';

    renderDigit(display, 0, hour / 10);
    renderDigit(display, 7, hour % 10);
    renderDigit(display, 17, minute / 10);
    renderDigit(display, 24, minute % 10);

    return display;
}

void addScanErrors(array<string, 7>& display, int mode) {
    int digitWindows[4][2] = {{0, 4}, {7, 11}, {17, 21}, {24, 28}};
    int dotBudget = rnd.next(1, mode == 0 ? 8 : mode == 1 ? 24 : 55);

    for (int used = 0; used < dotBudget; ++used) {
        int row = rnd.next(0, 6);
        int col;
        if (mode == 2 && rnd.next(0, 3) != 0) {
            int which = rnd.next(0, 3);
            col = rnd.next(digitWindows[which][0], digitWindows[which][1]);
        } else {
            col = rnd.next(0, 28);
        }
        display[row][col] = '.';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int displayCount = rnd.next(1, 6);
    int mode = rnd.next(0, 2);

    for (int i = 0; i < displayCount; ++i) {
        int hour = rnd.next(0, 23);
        int minute = rnd.next(0, 59);
        if (mode == 1 && i == 0) {
            hour = rnd.any(vector<int>{0, 1, 10, 11, 20, 21, 22, 23});
            minute = rnd.any(vector<int>{0, 1, 10, 11, 50, 51, 58, 59});
        }

        array<string, 7> display = renderTime(hour, minute);
        addScanErrors(display, mode);

        for (const string& line : display) {
            println(line);
        }
        println("");
        println("");
    }
    println("end");

    return 0;
}

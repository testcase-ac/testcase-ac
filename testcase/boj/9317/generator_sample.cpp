#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string decimalString(int wholeMin, int wholeMax, int maxDecimals) {
    int whole = rnd.next(wholeMin, wholeMax);
    int decimals = rnd.next(0, maxDecimals);
    if (decimals == 0) {
        return to_string(whole);
    }

    int scale = 1;
    for (int i = 0; i < decimals; ++i) {
        scale *= 10;
    }

    int fraction = rnd.next(0, scale - 1);
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%d.%0*d", whole, decimals, fraction);
    return string(buffer);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> commonResolutions = {
        {1, 1},       {800, 600},   {1024, 768},  {1280, 720},
        {1366, 768},  {1920, 1080}, {2560, 1440}, {3840, 2160},
    };

    int cases = rnd.next(1, 8);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 5);
        string diagonal;
        int horizontal;
        int vertical;

        if (mode == 0) {
            vector<string> commonDiagonals = {"10", "11.0", "13.3", "15.6", "24", "27", "32.5"};
            diagonal = rnd.any(commonDiagonals);
            auto resolution = rnd.any(commonResolutions);
            horizontal = resolution.first;
            vertical = resolution.second;
        } else if (mode == 1) {
            diagonal = decimalString(1, 80, 1);
            horizontal = rnd.next(1, 4000);
            vertical = rnd.next(1, 2500);
        } else if (mode == 2) {
            diagonal = decimalString(1, 5, 10);
            horizontal = rnd.next(1, 20);
            vertical = rnd.next(1, 20);
        } else if (mode == 3) {
            diagonal = decimalString(1000, 1000000, 3);
            horizontal = rnd.next(1, 1000000000);
            vertical = rnd.next(1, 1000000000);
        } else if (mode == 4) {
            diagonal = decimalString(6, 60, 10);
            horizontal = rnd.next(1, 100000);
            vertical = rnd.next(1, 100000);
        } else {
            diagonal = decimalString(1, 120, 4);
            horizontal = rnd.next(1, 1000000);
            vertical = rnd.next(1, 1000000);
        }

        println(diagonal, horizontal, vertical);
    }

    println("0 0 0");
    return 0;
}

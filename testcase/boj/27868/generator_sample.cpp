#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 0;
    int start = 0;
    int step = 1;
    string command;

    if (mode == 0) {
        n = rnd.next(2, 12);
        step = rnd.next(1, min(4, n - 1));
        bool up = rnd.next(0, 1);
        start = up ? rnd.next(1, n - step) : rnd.next(step + 1, n);
        command = up ? "+-" : "-+";
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        step = rnd.next(1, 3);
        int zeros = rnd.next(1, 4);
        bool up = rnd.next(0, 1);
        while (1 + zeros * step >= n) {
            --zeros;
        }
        if (up) {
            start = rnd.next(1, n - (zeros + 1) * step);
            command = "+" + string(zeros, '0') + "-";
        } else {
            start = rnd.next(1 + (zeros + 1) * step, n);
            command = "-" + string(zeros, '0') + "+";
        }
    } else if (mode == 2) {
        n = rnd.next(8, 24);
        step = rnd.next(1, 2);
        bool up = rnd.next(0, 1);
        if (up) {
            start = rnd.next(1, n - 4 * step);
            command = "++--";
        } else {
            start = rnd.next(1 + 4 * step, n);
            command = "--++";
        }
    } else if (mode == 3) {
        n = rnd.next(10, 30);
        step = 1;
        bool up = rnd.next(0, 1);
        if (up) {
            start = rnd.next(1, n - 7);
            command = "++0---+";
        } else {
            start = rnd.next(8, n);
            command = "--0+++-";
        }
    } else {
        n = rnd.next(6, 20);
        step = rnd.next(1, min(3, (n - 1) / 2));
        bool up = rnd.next(0, 1);
        if (up) {
            start = rnd.next(1, n - 2 * step);
            command = "+0-";
        } else {
            start = rnd.next(1 + 2 * step, n);
            command = "-0+";
        }
    }

    vector<int> acceleration(n, step);
    for (int& value : acceleration) {
        if (rnd.next(0, 4) == 0) {
            value = rnd.next(1, min(20, max(1, n)));
        }
    }

    long long floor = start;
    long long speed = 0;
    for (char c : command) {
        int current = (int)floor - 1;
        if (c == '+' || c == '-') {
            acceleration[current] = step;
            speed += (c == '+') ? step : -step;
        }
        floor += speed;
    }

    println(n, start);
    println(acceleration);
    println(command);

    return 0;
}

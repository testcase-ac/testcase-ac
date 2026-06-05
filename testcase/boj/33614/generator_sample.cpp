#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LIMIT = 10000000;
    int mode = rnd.next(0, 5);
    int T = 1;

    if (mode == 0) T = rnd.next(1, 4);
    else if (mode == 1) T = rnd.next(5, 25);
    else if (mode == 2) T = rnd.next(20, 120);
    else if (mode == 3) T = rnd.next(1, 8);
    else if (mode == 4) T = rnd.next(200, 1000);
    else T = rnd.next(2, 20);

    vector<array<int, 3>> cases(T);
    long long sum[3] = {0, 0, 0};

    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < 3; ++j) {
            int remainingCases = T - i - 1;
            int remainingBudget = LIMIT - sum[j];
            int maxValue = remainingBudget - remainingCases;
            int value = 1;

            if (mode == 0) {
                value = rnd.next(1, min(maxValue, 12));
            } else if (mode == 1) {
                int cap = min(maxValue, rnd.next(50, 5000));
                value = rnd.next(1, cap);
            } else if (mode == 2) {
                int cap = min(maxValue, rnd.next(1000, 200000));
                value = rnd.wnext(cap, 2) + 1;
            } else if (mode == 3) {
                if (i == 0) value = maxValue;
                else value = rnd.next(1, min(maxValue, 20));
            } else if (mode == 4) {
                value = rnd.next(1, min(maxValue, 1000));
            } else {
                if (rnd.next(0, 3) == 0) value = 1;
                else value = rnd.next(1, min(maxValue, 10000000));
            }

            cases[i][j] = value;
            sum[j] += value;
        }
    }

    if (mode == 5) {
        shuffle(cases.begin(), cases.end());
    }

    println(T);
    for (const auto& tc : cases) {
        println(tc[0], tc[1], tc[2]);
    }

    return 0;
}

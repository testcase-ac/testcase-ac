#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 1000000000;
    vector<pair<int, int>> cases;

    int targetT = rnd.next(12, 45);
    while ((int)cases.size() < targetT) {
        int mode = rnd.next(8);
        int n = 1, m = 1;

        if (mode == 0) {
            n = rnd.next(1, 30);
            m = rnd.next(1, 30);
        } else if (mode == 1) {
            n = rnd.next(MAX_N - 2000, MAX_N);
            m = rnd.next(MAX_N - 2000, MAX_N);
        } else if (mode == 2) {
            n = rnd.next(1, MAX_N);
            m = n;
        } else if (mode == 3) {
            int base = rnd.next(1, 50000);
            int maxMul = MAX_N / base;
            n = base * rnd.next(1, min(maxMul, 20000));
            m = base * rnd.next(1, min(maxMul, 20000));
        } else if (mode == 4) {
            int small = rnd.next(1, 1000);
            int large = rnd.next(MAX_N - 100000, MAX_N);
            if (rnd.next(2) == 0) {
                n = small;
                m = large;
            } else {
                n = large;
                m = small;
            }
        } else if (mode == 5) {
            int base = rnd.next(1, 1000000);
            n = base;
            m = min(MAX_N, base * rnd.next(1, 1000));
        } else if (mode == 6) {
            n = rnd.next(1, 1000000);
            m = n + rnd.next(0, min(1000, MAX_N - n));
        } else {
            n = rnd.next(1, MAX_N);
            m = rnd.next(1, MAX_N);
        }

        cases.push_back({n, m});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& test : cases) {
        println(test.first, test.second);
    }

    return 0;
}

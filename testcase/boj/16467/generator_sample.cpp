#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int T;
    if (mode == 0) {
        T = rnd.next(1, 8);
    } else if (mode == 1) {
        T = rnd.next(8, 25);
    } else if (mode == 5) {
        T = 100;
    } else {
        T = rnd.next(20, 70);
    }

    vector<pair<int, int>> tests;
    tests.reserve(T);

    for (int i = 0; i < T; ++i) {
        int K;
        int N;

        if (mode == 0) {
            K = rnd.next(0, 4);
            N = rnd.next(1, 12);
        } else if (mode == 1) {
            K = rnd.any(vector<int>{0, 1, 2, 9, 10});
            N = rnd.next(1, 120);
        } else if (mode == 2) {
            K = rnd.next(0, 10);
            N = rnd.next(1, 1000);
        } else if (mode == 3) {
            K = rnd.next(0, 10);
            N = rnd.next(99900000, 100000000);
        } else if (mode == 4) {
            K = rnd.next(0, 10);
            int base = K + 1;
            N = max(1, base + rnd.next(-2, 6));
        } else {
            K = i % 11;
            if (i % 5 == 0) {
                N = 100000000 - rnd.next(0, 20);
            } else {
                N = rnd.next(1, 200);
            }
        }

        tests.emplace_back(K, N);
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (const auto& test : tests) {
        println(test.first, test.second);
    }

    return 0;
}

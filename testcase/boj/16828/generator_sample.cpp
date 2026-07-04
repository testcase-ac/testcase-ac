#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int C;
    int N;
    int M;
    vector<pair<int, int>> gifts;

    if (mode == 0) {
        C = rnd.next(1, 6);
        N = rnd.next(1, 6);
        M = rnd.next(1, 8);
        for (int i = 0; i < N; ++i) {
            gifts.push_back({rnd.next(1, C), rnd.next(1, 30)});
        }
    } else if (mode == 1) {
        C = rnd.next(1, 12);
        N = rnd.next(3, 9);
        M = rnd.next(2, 12);
        for (int i = 0; i < N; ++i) {
            int size = rnd.next(1, C + 8);
            int price = rnd.next(1, 80);
            gifts.push_back({size, price});
        }
    } else if (mode == 2) {
        C = rnd.next(10, 80);
        N = rnd.next(5, 14);
        M = rnd.next(1, 20);
        int baseSize = rnd.next(1, max(1, C / 4));
        for (int i = 0; i < N; ++i) {
            int size = min(10000, baseSize + rnd.next(0, 5));
            int price = rnd.next(1, 120);
            gifts.push_back({size, price});
        }
    } else if (mode == 3) {
        C = rnd.next(1, 40);
        N = rnd.next(1, 5);
        M = rnd.next(80, 220);
        for (int i = 0; i < N; ++i) {
            gifts.push_back({rnd.next(1, min(10000, C + 20)), rnd.next(1, 200)});
        }
    } else if (mode == 4) {
        C = rnd.next(100, 10000);
        N = rnd.next(4, 12);
        M = rnd.next(4, 40);
        for (int i = 0; i < N; ++i) {
            int size = (i % 3 == 0) ? rnd.next(max(1, C - 20), C) : rnd.next(1, min(10000, C));
            int price = rnd.next(1, 10000);
            gifts.push_back({size, price});
        }
    } else {
        C = rnd.next(1, 10000);
        N = rnd.next(1, 15);
        M = rnd.next(1, 60);
        for (int i = 0; i < N; ++i) {
            gifts.push_back({rnd.next(1, 10000), rnd.next(1, 10000)});
        }
    }

    shuffle(gifts.begin(), gifts.end());

    println(C, N, M);
    for (const auto& gift : gifts) {
        println(gift.first, gift.second);
    }

    return 0;
}

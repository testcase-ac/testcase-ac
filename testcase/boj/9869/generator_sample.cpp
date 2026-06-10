#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<pair<int, int>> cows;

    auto addCow = [&](int milk, int deadline) {
        cows.push_back({milk, deadline});
    };

    if (mode == 0) {
        n = rnd.next(2, 12);
        int deadline = rnd.next(1, min(4, n));
        for (int i = 0; i < n; ++i) {
            int milk = rnd.next(1, 1000);
            addCow(milk, deadline);
        }
    } else if (mode == 1) {
        n = rnd.next(5, 18);
        for (int i = 0; i < n; ++i) {
            int deadline = rnd.next(1, min(n, 6));
            int milk = (i % 3 == 0) ? rnd.next(800, 1000) : rnd.next(1, 300);
            addCow(milk, deadline);
        }
    } else if (mode == 2) {
        n = rnd.next(6, 20);
        int lateBase = rnd.next(9000, 10000);
        for (int i = 0; i < n; ++i) {
            int deadline = (i % 4 == 0) ? rnd.next(1, 3) : rnd.next(lateBase, 10000);
            int milk = rnd.next(1, 1000);
            addCow(milk, deadline);
        }
    } else if (mode == 3) {
        n = rnd.next(8, 25);
        for (int i = 1; i <= n; ++i) {
            int deadline = rnd.next(max(1, i - 2), min(10000, i + 2));
            int milk = 1000 - rnd.next(0, min(900, i * rnd.next(1, 5)));
            addCow(milk, deadline);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 30);
        int groups = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) {
            int group = rnd.next(1, groups);
            int deadline = group * rnd.next(1, 3);
            int milk = rnd.next(1, 1000);
            addCow(milk, min(deadline, 10000));
        }
    } else {
        n = rnd.next(40, 120);
        for (int i = 0; i < n; ++i) {
            int deadline;
            if (rnd.next(0, 4) == 0) {
                deadline = rnd.next(1, 10);
            } else {
                deadline = rnd.next(1, min(10000, n + 20));
            }
            int milk = rnd.next(1, 1000);
            addCow(milk, deadline);
        }
    }

    shuffle(cows.begin(), cows.end());

    println((int)cows.size());
    for (auto [milk, deadline] : cows) {
        println(milk, deadline);
    }

    return 0;
}

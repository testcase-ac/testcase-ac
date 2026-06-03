#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 60);
    vector<pair<int, int>> homework;
    homework.reserve(n);

    if (mode == 0) {
        int deadline = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int reward = rnd.next(1, 2000000);
            homework.push_back({deadline, reward});
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            int deadline = i;
            int reward = rnd.next(1, 2000000);
            homework.push_back({deadline, reward});
        }
    } else if (mode == 2) {
        int early = rnd.next(1, max(1, n / 3));
        int late = rnd.next(max(early, n - n / 3), n);
        for (int i = 0; i < n; ++i) {
            int deadline = rnd.next(0, 1) ? early : late;
            int reward = rnd.next(1, 2000000);
            homework.push_back({deadline, reward});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int deadline = rnd.wnext(n, -2) + 1;
            int reward = 1 + rnd.wnext(2000000, 3);
            homework.push_back({deadline, reward});
        }
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        int topReward = rnd.next(1000000000, 2147483647);
        homework.push_back({1, topReward});
        for (int i = 1; i < n; ++i) {
            int deadline = 1;
            int reward = rnd.next(1, min(1000000, topReward - 1));
            homework.push_back({deadline, reward});
        }
    } else {
        n = rnd.next(20, 80);
        int rewardBase = rnd.next(1, 500000);
        for (int i = 0; i < n; ++i) {
            int deadline = rnd.next(1, n);
            int reward = rewardBase + rnd.next(0, 500000);
            homework.push_back({deadline, reward});
        }
    }

    shuffle(homework.begin(), homework.end());

    println(n);
    for (auto [deadline, reward] : homework) {
        println(deadline, reward);
    }

    return 0;
}

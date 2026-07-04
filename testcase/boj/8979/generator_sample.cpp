#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Medal {
    int gold;
    int silver;
    int bronze;
};

Medal randomMedal(int hi) {
    return {rnd.next(0, hi), rnd.next(0, hi), rnd.next(0, hi)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int k = 1;
    vector<Medal> medals;

    if (mode == 0) {
        n = rnd.next(1, 12);
        k = rnd.next(1, n);
        Medal same = randomMedal(8);
        medals.assign(n, same);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        k = rnd.next(1, n);
        int current = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 2) != 0) current += rnd.next(0, 2);
            medals.push_back({current, 0, 0});
        }
        shuffle(medals.begin(), medals.end());
    } else if (mode == 2) {
        int better = rnd.next(0, 5);
        int tied = rnd.next(2, 6);
        int worse = rnd.next(0, 5);
        n = better + tied + worse;
        k = better + rnd.next(1, tied);

        Medal target = {rnd.next(1, 9), rnd.next(1, 9), rnd.next(1, 9)};
        for (int i = 0; i < better; ++i) {
            int bump = rnd.next(0, 2);
            if (bump == 0) {
                medals.push_back({target.gold + rnd.next(1, 5), rnd.next(0, 9), rnd.next(0, 9)});
            } else if (bump == 1) {
                medals.push_back({target.gold, target.silver + rnd.next(1, 5), rnd.next(0, 9)});
            } else {
                medals.push_back({target.gold, target.silver, target.bronze + rnd.next(1, 5)});
            }
        }
        for (int i = 0; i < tied; ++i) medals.push_back(target);
        for (int i = 0; i < worse; ++i) {
            int drop = rnd.next(0, 2);
            if (drop == 0) {
                medals.push_back({rnd.next(0, target.gold - 1), rnd.next(0, 9), rnd.next(0, 9)});
            } else if (drop == 1) {
                medals.push_back({target.gold, rnd.next(0, target.silver - 1), rnd.next(0, 9)});
            } else {
                medals.push_back({target.gold, target.silver, rnd.next(0, target.bronze - 1)});
            }
        }
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        k = rnd.next(1, n);
        int baseGold = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            medals.push_back({baseGold + rnd.next(0, 1), rnd.next(0, 12), rnd.next(0, 12)});
        }
    } else if (mode == 4) {
        n = rnd.next(10, 60);
        k = rnd.next(1, n);
        int hi = rnd.any(vector<int>{1, 3, 10, 30, 100});
        for (int i = 0; i < n; ++i) medals.push_back(randomMedal(hi));
    } else {
        n = rnd.next(80, 160);
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int tier = i % 8;
            medals.push_back({7 - tier, rnd.next(0, 4), rnd.next(0, 4)});
        }
        shuffle(medals.begin(), medals.end());
    }

    vector<int> ids(n);
    for (int i = 0; i < n; ++i) ids[i] = i + 1;
    shuffle(ids.begin(), ids.end());

    println(n, k);
    for (int id : ids) {
        Medal m = medals[id - 1];
        println(id, m.gold, m.silver, m.bronze);
    }

    return 0;
}

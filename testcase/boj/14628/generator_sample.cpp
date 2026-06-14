#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 8);
    int m;
    int k;
    vector<pair<int, int>> skills;

    if (mode == 0) {
        m = rnd.next(1, 25);
        k = rnd.next(1, 100);
        skills.push_back({rnd.next(1, 100), m});
    } else if (mode == 1) {
        int y = rnd.next(1, 12);
        int times = rnd.next(2, 7);
        m = y * times;
        k = rnd.next(1, 100);
        skills.push_back({rnd.next(1, 30), y});
    } else if (mode == 2) {
        int a = rnd.next(2, 12);
        int b = rnd.next(2, 12);
        int ca = rnd.next(1, 4);
        int cb = rnd.next(1, 4);
        m = a * ca + b * cb;
        k = rnd.next(1, 25);
        skills.push_back({rnd.next(1, 40), a});
        skills.push_back({rnd.next(1, 40), b});
    } else if (mode == 3) {
        int g = rnd.next(2, 10);
        int target = rnd.next(2, 10) * g;
        m = target;
        k = rnd.next(60, 100);
        skills.push_back({rnd.next(1, 25), g});
        skills.push_back({rnd.next(1, 25), rnd.next(1, target / g) * g});
    } else if (mode == 4) {
        m = rnd.next(20, 60);
        k = rnd.next(1, 100);
        skills.push_back({rnd.next(1, 10), 1});
    } else {
        m = rnd.next(1, 100);
        k = rnd.next(1, 100);
        int first = rnd.next(1, m);
        int second = m - first;
        skills.push_back({rnd.next(1, 100), first});
        if (second > 0) {
            skills.push_back({rnd.next(1, 100), second});
        }
    }

    while ((int)skills.size() < n) {
        skills.push_back({rnd.next(1, 100), rnd.next(1, 100)});
    }
    shuffle(skills.begin(), skills.end());

    println((int)skills.size(), m, k);
    for (auto [x, y] : skills) {
        println(x, y);
    }

    return 0;
}

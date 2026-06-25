#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int maxSecond = 2880;
    vector<int> aTimes;
    vector<int> bTimes;

    auto add = [&](vector<int>& target, set<int>& used, int second) {
        if (second < 1 || second > maxSecond || used.count(second)) return false;
        used.insert(second);
        target.push_back(second);
        return true;
    };

    set<int> used;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        int start = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            add((i % 2 == 0) ? aTimes : bTimes, used, start + i);
        }
    } else if (mode == 1) {
        int n = rnd.next(4, 18);
        int center = rnd.next(1428, 1452);
        int cur = center - n / 2;
        for (int i = 0; i < n; ++i) {
            add((i % 3 == 0) ? bTimes : aTimes, used, cur + i);
        }
    } else if (mode == 2) {
        int a = rnd.next(1, 12);
        int b = rnd.next(1, 12);
        for (int i = 0; i < a; ++i) add(aTimes, used, rnd.next(1, 1439));
        for (int i = 0; i < b; ++i) add(bTimes, used, rnd.next(1440, 2880));
    } else if (mode == 3) {
        int n = rnd.next(6, 26);
        int cur = rnd.next(1, 120);
        for (int i = 0; i < n && cur <= maxSecond; ++i) {
            bool teamA = (i % 4 == 0 || i % 4 == 1);
            add(teamA ? aTimes : bTimes, used, cur);
            cur += rnd.next(1, 90);
        }
    } else if (mode == 4) {
        vector<int> anchors = {1, 2, 3, 1439, 1440, 1441, 2878, 2879, 2880};
        shuffle(anchors.begin(), anchors.end());
        int take = rnd.next(2, (int)anchors.size());
        for (int i = 0; i < take; ++i) {
            add((i % 2 == 0) ? aTimes : bTimes, used, anchors[i]);
        }
    } else {
        int n = rnd.next(10, 40);
        int currentLead = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            int second = rnd.next(1, maxSecond);
            while (used.count(second)) second = rnd.next(1, maxSecond);
            if (rnd.next(0, 3) == 0) currentLead ^= 1;
            add(currentLead == 0 ? aTimes : bTimes, used, second);
        }
    }

    if (aTimes.empty()) {
        int second = 1;
        while (used.count(second)) ++second;
        add(aTimes, used, second);
    }
    if (bTimes.empty()) {
        int second = 2;
        while (used.count(second)) ++second;
        add(bTimes, used, second);
    }

    sort(aTimes.begin(), aTimes.end());
    sort(bTimes.begin(), bTimes.end());

    println((int)aTimes.size());
    for (int second : aTimes) println(second);
    println((int)bTimes.size());
    for (int second : bTimes) println(second);

    return 0;
}

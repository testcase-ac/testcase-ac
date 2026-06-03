#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int s;
    vector<int> singerCount(3);

    if (mode == 0) {
        s = rnd.next(1, 6);
        for (int& x : singerCount) x = rnd.next(1, s);
    } else if (mode == 1) {
        s = rnd.next(1, 10);
        singerCount = {1, 1, 1};
        singerCount[rnd.next(3)] = s;
    } else if (mode == 2) {
        s = rnd.next(2, 20);
        int low = max(1, s / 2 - 2);
        int high = min(s, s / 2 + 3);
        for (int& x : singerCount) x = rnd.next(low, high);
    } else if (mode == 3) {
        s = rnd.next(10, 50);
        int center = rnd.next(max(1, s - 8), s);
        for (int& x : singerCount) x = rnd.next(max(1, center - 3), s);
    } else if (mode == 4) {
        s = rnd.next(2, 50);
        int total = rnd.next(1, s - 1);
        singerCount = {1, 1, 1};
        for (int i = 0; i < total - 3 && total >= 3; ++i) {
            int idx = rnd.next(3);
            if (singerCount[idx] < s) ++singerCount[idx];
        }
    } else if (mode == 5) {
        s = 50;
        for (int& x : singerCount) x = rnd.next(1, 50);
    } else {
        s = rnd.next(1, 50);
        for (int& x : singerCount) x = rnd.next(1, s);
        if (rnd.next(2) == 0) singerCount[rnd.next(3)] = s;
    }

    shuffle(singerCount.begin(), singerCount.end());
    println(s, singerCount[0], singerCount[1], singerCount[2]);
    return 0;
}

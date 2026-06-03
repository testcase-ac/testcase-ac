#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeCase() {
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<int> s;

    if (mode == 0) {
        int hi = rnd.next(4, 12);
        for (int i = 0; i < n; ++i) s.push_back(rnd.next(4, hi));
    } else if (mode == 1) {
        int bottleneck = rnd.next(4, 9);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 75) {
                s.push_back(rnd.next(4, bottleneck));
            } else {
                s.push_back(rnd.next(bottleneck + 1, 25));
            }
        }
    } else if (mode == 2) {
        n = rnd.next(4, 20);
        int offset = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) s.push_back(max(4, i + 1 + offset + rnd.next(0, 2)));
        shuffle(s.begin(), s.end());
    } else if (mode == 3) {
        int value = rnd.next(4, 1000000);
        for (int i = 0; i < n; ++i) s.push_back(value);
    } else if (mode == 4) {
        n = rnd.next(2, 16);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 35) {
                s.push_back(rnd.next(999990, 1000000));
            } else {
                s.push_back(rnd.next(4, 20));
            }
        }
    } else {
        n = rnd.next(8, 22);
        int clusterCount = rnd.next(2, 4);
        vector<int> clusters;
        for (int i = 0; i < clusterCount; ++i) clusters.push_back(rnd.next(4, 25));
        sort(clusters.begin(), clusters.end());
        for (int i = 0; i < n; ++i) s.push_back(rnd.any(clusters) + rnd.next(0, 2));
    }

    shuffle(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int caseIdx = 0; caseIdx < t; ++caseIdx) {
        vector<int> s = makeCase();
        println((int)s.size());
        println(s);
    }

    return 0;
}

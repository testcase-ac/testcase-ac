#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int groups = rnd.next(1, 7);
    int rem = rnd.next(0, 3);
    int n = 4 * groups + rem;
    vector<long long> skills;

    if (mode == 0) {
        long long cur = rnd.next(1, 30);
        for (int g = 0; g < groups; ++g) {
            long long width = rnd.next(0, 8);
            for (int i = 0; i < 4; ++i) skills.push_back(cur + rnd.next(0LL, width));
            cur += width + rnd.next(3, 25);
        }
        for (int i = 0; i < rem; ++i) skills.push_back(cur + rnd.next(20, 80));
    } else if (mode == 1) {
        long long base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            long long value = base + (i / 4) * rnd.next(1, 6) + rnd.next(0, 2);
            skills.push_back(value);
        }
    } else if (mode == 2) {
        vector<long long> pool;
        int distinct = rnd.next(1, min(8, n));
        long long base = rnd.next(1, 1000000);
        for (int i = 0; i < distinct; ++i) pool.push_back(base + rnd.next(0, 20));
        for (int i = 0; i < n; ++i) skills.push_back(rnd.any(pool));
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) skills.push_back(rnd.next(1LL, 25LL));
            else skills.push_back(1000000000LL - rnd.next(0LL, 25LL));
        }
    } else if (mode == 4) {
        n = rnd.next(4, 60);
        for (int i = 0; i < n; ++i) skills.push_back(rnd.next(1LL, 1000000000LL));
    } else {
        int wantedRem = rnd.next(0, 3);
        n = 4 * rnd.next(1, 8) + wantedRem;
        long long low = rnd.next(1, 200);
        long long high = rnd.next(999999800LL, 999999997LL);
        for (int i = 0; i < n; ++i) {
            long long anchor = (i % 5 == 0) ? high : low + (i / 4) * 10;
            skills.push_back(anchor + rnd.next(0LL, 3LL));
        }
    }

    shuffle(skills.begin(), skills.end());

    println((int)skills.size());
    println(skills);
    return 0;
}

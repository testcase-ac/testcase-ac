#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(8, 15);
    vector<vector<int>> allTimes;
    vector<int> ks;

    for (int tc = 0; tc < z; ++tc) {
        int mode = rnd.next(8);
        int n;
        int k;
        vector<int> times;

        if (mode == 0) {
            n = 1;
            k = 0;
            times.push_back(rnd.next(0, 3));
        } else if (mode == 1) {
            n = rnd.next(2, 8);
            k = 0;
            int hi = rnd.next(0, 20);
            for (int i = 0; i < n; ++i) times.push_back(rnd.next(0, hi));
        } else if (mode == 2) {
            n = rnd.next(2, 10);
            k = n - 1;
            int base = rnd.next(0, 12);
            for (int i = 0; i < n; ++i) times.push_back(max(0, base + rnd.next(-2, 2)));
        } else if (mode == 3) {
            n = rnd.next(3, 12);
            k = rnd.next(1, n - 2);
            for (int i = 0; i < n; ++i) times.push_back(rnd.next(0, 1) ? 0 : rnd.next(1, 25));
        } else if (mode == 4) {
            n = rnd.next(3, 12);
            k = rnd.next(0, n - 1);
            int heavy = rnd.next(100000000, 1000000000);
            times.push_back(heavy);
            for (int i = 1; i < n; ++i) times.push_back(rnd.next(0, 100));
        } else if (mode == 5) {
            n = rnd.next(4, 14);
            k = rnd.next(1, n - 1);
            int a = rnd.next(0, 10);
            int b = rnd.next(10, 30);
            for (int i = 0; i < n; ++i) times.push_back(rnd.next(0, 2) == 0 ? a : b);
        } else if (mode == 6) {
            n = rnd.next(5, 15);
            k = rnd.next(0, n - 1);
            for (int i = 0; i < n; ++i) times.push_back((i + 1) * rnd.next(1, 7));
            if (rnd.next(2)) reverse(times.begin(), times.end());
        } else {
            n = rnd.next(2, 18);
            k = rnd.next(0, n - 1);
            int hi = rnd.next(5, 60);
            for (int i = 0; i < n; ++i) times.push_back(rnd.next(0, hi));
        }

        shuffle(times.begin(), times.end());
        allTimes.push_back(times);
        ks.push_back(k);
    }

    println(z);
    for (int tc = 0; tc < z; ++tc) {
        println((int)allTimes[tc].size(), ks[tc]);
        println(allTimes[tc]);
    }

    return 0;
}

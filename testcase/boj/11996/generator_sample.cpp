#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 4) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(3, 20);
    }

    vector<int> cows(n, 0);

    if (mode == 0) {
        fill(cows.begin(), cows.end(), 1);
    } else if (mode == 1) {
        cows[rnd.next(n)] = n;
    } else if (mode == 2) {
        int clusters = rnd.next(2, min(n, 5));
        vector<int> centers;
        while ((int)centers.size() < clusters) {
            int pos = rnd.next(n);
            if (find(centers.begin(), centers.end(), pos) == centers.end()) {
                centers.push_back(pos);
            }
        }
        for (int cow = 0; cow < n; ++cow) {
            int center = rnd.any(centers);
            int offset = rnd.next(0, min(n - 1, 3));
            cows[(center + offset) % n]++;
        }
    } else if (mode == 3) {
        int remaining = n;
        for (int i = 0; i < n; ++i) {
            int take = rnd.next(0, min(remaining, 3));
            cows[i] = take;
            remaining -= take;
        }
        while (remaining > 0) {
            cows[rnd.next(n)]++;
            remaining--;
        }
        shuffle(cows.begin(), cows.end());
    } else {
        int remaining = n;
        int pos = rnd.next(n);
        while (remaining > 0) {
            int take = min(remaining, rnd.next(1, 6));
            cows[pos] += take;
            remaining -= take;
            pos = (pos + rnd.next(1, 7)) % n;
        }
    }

    println(n);
    for (int cowCount : cows) {
        println(cowCount);
    }

    return 0;
}

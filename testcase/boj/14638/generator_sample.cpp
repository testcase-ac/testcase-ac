#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int d;
    if (mode == 0) {
        d = 1;
    } else if (mode == 1) {
        d = rnd.next(2, 6);
    } else {
        d = rnd.next(3, 14);
    }

    vector<int> reds;
    if (mode == 0) {
        reds.push_back(rnd.next(0, 255));
    } else if (mode == 2) {
        int start = rnd.next(0, 255 - d + 1);
        for (int i = 0; i < d; ++i) reds.push_back(start + i);
    } else if (mode == 3) {
        reds.push_back(0);
        reds.push_back(255);
        while ((int)reds.size() < d) reds.push_back(rnd.next(0, 255));
        sort(reds.begin(), reds.end());
        reds.erase(unique(reds.begin(), reds.end()), reds.end());
        while ((int)reds.size() < d) {
            int candidate = rnd.next(0, 255);
            if (!binary_search(reds.begin(), reds.end(), candidate)) {
                reds.insert(lower_bound(reds.begin(), reds.end(), candidate), candidate);
            }
        }
    } else {
        vector<int> candidates;
        for (int r = 0; r <= 255; ++r) candidates.push_back(r);
        shuffle(candidates.begin(), candidates.end());
        candidates.resize(d);
        sort(candidates.begin(), candidates.end());
        reds = candidates;
    }

    int k;
    if (mode == 1) {
        k = d;
    } else if (mode == 4) {
        k = 1;
    } else if (mode == 5) {
        k = rnd.next(1, min(d, 3));
    } else {
        k = rnd.next(1, d);
    }

    vector<long long> pixels;
    for (int i = 0; i < d; ++i) {
        long long p;
        if (mode == 3 && (reds[i] == 0 || reds[i] == 255)) {
            p = 67108864LL;
        } else if (mode == 4) {
            p = (i % 2 == 0) ? rnd.next(1, 20) : rnd.next(1000000, 67108864);
        } else if (mode == 5) {
            p = rnd.next(1, 1000) * 1000LL;
        } else {
            p = rnd.next(1, 200000);
        }
        pixels.push_back(p);
    }

    println(d, k);
    for (int i = 0; i < d; ++i) {
        println(reds[i], pixels[i]);
    }

    return 0;
}

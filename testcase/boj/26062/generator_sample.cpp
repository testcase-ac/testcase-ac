#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(100);
    int n;
    if (sizeMode < 20) {
        n = 3;
    } else if (sizeMode < 80) {
        n = rnd.next(4, 12);
    } else {
        n = rnd.next(13, 40);
    }

    int pattern = rnd.next(6);
    vector<int> s(n);

    if (pattern == 0) {
        int value = rnd.next(1, 20);
        fill(s.begin(), s.end(), value);
    } else if (pattern == 1) {
        int value = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            value += rnd.next(0, 5);
            s[i] = value;
        }
    } else if (pattern == 2) {
        int value = rnd.next(1, 8);
        for (int i = n - 1; i >= 0; --i) {
            value += rnd.next(0, 5);
            s[i] = value;
        }
    } else if (pattern == 3) {
        int peak = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            int distance = abs(i - peak);
            s[i] = rnd.next(1, 7) + max(0, 20 - 3 * distance);
        }
    } else if (pattern == 4) {
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(1, 100);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(1, 1000000000);
        }
    }

    long long total = accumulate(s.begin(), s.end(), 0LL);
    long long maxSingle = *max_element(s.begin(), s.end());

    vector<long long> candidates;
    candidates.push_back(1);
    candidates.push_back(maxSingle);
    candidates.push_back(min(100000000000000LL, maxSingle + rnd.next(0, 20)));
    candidates.push_back(min(100000000000000LL, total));
    candidates.push_back(100000000000000LL);

    int center = rnd.next(n);
    long long windowSum = 0;
    int radius = rnd.next(0, min(4, n - 1));
    for (int i = max(0, center - radius); i <= min(n - 1, center + radius); ++i) {
        windowSum += s[i];
    }
    candidates.push_back(max(1LL, windowSum - rnd.next(0, 3)));
    candidates.push_back(min(100000000000000LL, windowSum + rnd.next(0, 3)));

    long long r = rnd.any(candidates);
    r = max(1LL, min(100000000000000LL, r));

    println(n, r);
    println(s);

    return 0;
}

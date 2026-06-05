#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomValue() {
    const int mode = rnd.next(0, 3);
    if (mode == 0) return rnd.next(0, 20);
    if (mode == 1) return rnd.next(999999950LL, 1000000000LL);
    return rnd.next(0LL, 1000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_KEY_VALUE = 1000000000LL;
    const int kModes[] = {1, 2, 3, 5, 10, 10000};
    const int k = rnd.any(vector<int>(begin(kModes), end(kModes)));
    const int n = rnd.next(2, 8);
    const int m = rnd.next(8, 24);

    vector<long long> keys;
    const long long base = rnd.next(0LL, 200LL);
    long long current = base;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            int gapMode = rnd.next(0, 3);
            if (gapMode == 0) current += rnd.next(1, max(1, k));
            else if (gapMode == 1) current += k + rnd.next(1, max(1, k + 2));
            else current += 2LL * k + rnd.next(1, 20);
        }
        keys.push_back(current);
    }

    println(n, m, k);
    for (long long key : keys) {
        println(key, randomValue());
    }

    for (int i = 0; i < m; ++i) {
        sort(keys.begin(), keys.end());

        int command = rnd.next(1, 3);
        if (i == 0) command = 3;
        if (i == 1) command = 2;

        if (command == 1) {
            long long key = 0;
            for (int attempt = 0; attempt < 100; ++attempt) {
                int pos = rnd.next(0, static_cast<int>(keys.size()));
                long long candidate;
                if (pos == 0) {
                    candidate = keys.front() + rnd.next(1, 2 * k + 30);
                } else if (pos == static_cast<int>(keys.size())) {
                    candidate = keys.back() + rnd.next(1, 2 * k + 30);
                } else {
                    candidate = keys[pos - 1] + rnd.next(1LL, max(1LL, keys[pos] - keys[pos - 1] - 1));
                }

                if (0 <= candidate && candidate <= MAX_KEY_VALUE &&
                    !binary_search(keys.begin(), keys.end(), candidate)) {
                    key = candidate;
                    break;
                }
            }

            if (binary_search(keys.begin(), keys.end(), key)) {
                key = keys.back() + 1;
            }
            keys.push_back(key);
            println(1, key, randomValue());
            continue;
        }

        long long query = rnd.any(keys);
        int queryMode = rnd.next(0, 5);
        if (keys.size() >= 2 && queryMode <= 2) {
            int pos = rnd.next(1, static_cast<int>(keys.size()) - 1);
            long long left = keys[pos - 1];
            long long right = keys[pos];
            if (queryMode == 0 && (right - left) % 2 == 0) {
                query = (left + right) / 2;
            } else if (queryMode == 1 && right - left > 2) {
                query = left + rnd.next(1LL, right - left - 1);
            } else if (right - left > 2LL * k + 2) {
                query = left + k + 1;
            }
        } else if (queryMode == 3) {
            query = rnd.any(keys);
        } else {
            long long anchor = rnd.any(keys);
            query = max(keys.front(), min(keys.back(), anchor + rnd.next(-k, k)));
        }

        if (command == 2) {
            println(2, query, randomValue());
        } else {
            println(3, query);
        }
    }

    return 0;
}

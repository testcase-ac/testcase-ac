#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> buildIntervals(int k, int maxTime, int mode) {
    vector<pair<int, int>> intervals;
    if (mode == 0) {
        int cursor = rnd.next(0, min(3, maxTime - 1));
        for (int i = 0; i < k; ++i) {
            int remaining = k - i - 1;
            int latestStart = maxTime - 1 - 2 * remaining;
            cursor = min(cursor + rnd.next(0, 2), latestStart);
            int maxLen = min(8, maxTime - cursor - 2 * remaining);
            int len = rnd.next(1, maxLen);
            intervals.push_back({cursor, cursor + len});
            cursor += len + rnd.next(1, 3);
        }
    } else if (mode == 1) {
        int cursor = max(0, maxTime - (2 * k + rnd.next(1, 12)));
        for (int i = 0; i < k; ++i) {
            int remaining = k - i - 1;
            int latestStart = maxTime - 1 - 2 * remaining;
            cursor = min(cursor + rnd.next(0, 1), latestStart);
            int maxLen = max(1, min(5, maxTime - cursor - 2 * remaining));
            int len = rnd.next(1, maxLen);
            intervals.push_back({cursor, cursor + len});
            cursor += len + 1;
        }
    } else {
        int bucket = max(2, maxTime / (k + 1));
        for (int i = 0; i < k; ++i) {
            int start = min(maxTime - 1, i * bucket + rnd.next(0, max(0, bucket / 2)));
            if (!intervals.empty()) {
                start = max(start, intervals.back().second + 1);
            }
            int remaining = k - i - 1;
            start = min(start, maxTime - 1 - 2 * remaining);
            int len = rnd.next(1, min(bucket, maxTime - start - 2 * remaining));
            intervals.push_back({start, start + len});
        }
    }
    return intervals;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = (mode == 0 ? rnd.next(1, 4) : rnd.next(3, 12));
    int t;
    int maxTime;
    if (mode == 1) {
        maxTime = rnd.next(99980, 100000);
        t = rnd.next(max(1, maxTime - 25), 100000);
    } else if (mode == 2) {
        maxTime = rnd.next(12, 35);
        t = rnd.next(1, min(12, maxTime));
    } else {
        maxTime = rnd.next(6, 60);
        t = rnd.next(1, maxTime);
    }

    println(n, t);
    for (int participant = 0; participant < n; ++participant) {
        int maxK = max(1, min(6, (maxTime + 1) / 2));
        int k = mode == 0 ? 1 : rnd.next(1, maxK);
        vector<pair<int, int>> intervals = buildIntervals(k, maxTime, mode % 3);

        println(k);
        for (auto interval : intervals) {
            println(interval.first, interval.second);
        }
    }

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    const long long max_height = 2147483647LL;
    vector<long long> front(n), side(m);
    for (int i = 0; i < n; ++i) {
        // CHECK: The Korean BOJ statement allows heights up to 2^31-1; the English variant's 5000 limit is not used here.
        front[i] = inf.readLong(0LL, max_height, "front_i");
        inf.readEoln();
    }
    for (int i = 0; i < m; ++i) {
        side[i] = inf.readLong(0LL, max_height, "side_i");
        inf.readEoln();
    }

    long long max_front = *max_element(front.begin(), front.end());
    long long max_side = *max_element(side.begin(), side.end());
    if (max_front == max_side) {
        sort(side.begin(), side.end());

        vector<__int128_t> prefix(m + 1, 0);
        for (int i = 0; i < m; ++i) {
            prefix[i + 1] = prefix[i] + side[i];
        }

        __int128_t max_blocks = 0;
        for (long long height : front) {
            int le_count = upper_bound(side.begin(), side.end(), height) - side.begin();
            max_blocks += prefix[le_count] + static_cast<__int128_t>(m - le_count) * height;
        }

        ensuref(max_blocks <= max_height, "maximum block count exceeds 2^31-1");
    }

    inf.readEof();
}

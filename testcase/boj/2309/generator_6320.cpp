#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate 7 distinct positive integers summing to 100
    vector<int> core;
    int k = 7, rem = 100, prev = 0;
    for (int i = 0; i < 6; i++) {
        // For current k slots, we need to pick x in [prev+1 .. x_max]
        // so that remaining k-1 distinct values (each >= x+1) sum <= rem - x.
        int min_v = prev + 1;
        // minimal sum of next k-1 values if they were consecutive: sum_{j=1..k-1}(j) = (k-1)*k/2
        int min_sum_future = (k - 1) * k / 2;
        // Solve rem >= k*x + min_sum_future  => x <= (rem - min_sum_future)/k
        int x_max = (rem - min_sum_future) / k;
        if (x_max < min_v) x_max = min_v;
        int span = x_max - min_v + 1;
        int x;
        if (span <= 1) {
            x = min_v;
        } else if (rnd.next(0, 2) == 0) {
            // uniform
            x = rnd.next(min_v, x_max);
        } else {
            // biased via wnext
            int t = rnd.next(-2, 2);
            x = min_v + rnd.wnext(span, t);
            if (x > x_max) x = x_max;
        }
        core.push_back(x);
        rem -= x;
        prev = x;
        k--;
    }
    // Last remaining value
    core.push_back(rem);
    // core is sorted and has 7 distinct values summing to 100.

    // Generate 2 extra dwarves distinct from core, in [1..100]
    vector<int> pool;
    for (int v = 1; v <= 100; v++) {
        if (!binary_search(core.begin(), core.end(), v))
            pool.push_back(v);
    }
    int y1 = rnd.any(pool);
    pool.erase(find(pool.begin(), pool.end(), y1));
    int y2 = rnd.any(pool);

    // Combine and shuffle
    vector<int> all = core;
    all.push_back(y1);
    all.push_back(y2);
    shuffle(all.begin(), all.end());

    // Output 9 heights, one per line
    for (int h : all)
        println(h);

    return 0;
}

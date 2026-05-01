#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Occasionally output fixed sample tests
    int fixed = rnd.next(0, 19);
    if (fixed == 0) {
        println(4, 10); // sample 1
        return 0;
    }
    if (fixed == 1) {
        println(8, 19); // sample 2
        return 0;
    }

    // Choose k with bias toward smaller values but allowing larger ones
    int bucket = rnd.next(0, 9);
    int k;
    if (bucket < 4) {          // 40% very small
        k = rnd.next(1, 3);    // n = 2..8
    } else if (bucket < 7) {   // 30% small/medium
        k = rnd.next(4, 7);    // n = 16..128
    } else if (bucket < 9) {   // 20% medium/large
        k = rnd.next(8, 10);   // n = 256..1024
    } else {                   // 10% large
        k = rnd.next(11, 15);  // n = 2048..32768
    }

    int n = 1 << k;
    long long total = 1LL * n * n; // max 2^30

    // Build a set of special step counts m to hit tricky positions
    vector<long long> special;
    auto add = [&](long long v) {
        if (v >= 1 && v <= total) special.push_back(v);
    };

    add(1);
    add(2);
    add(3);
    add(total);
    add(total - 1);
    add(n);
    add(n + 1);
    add(n - 1);
    add(total / 2);
    add(total / 2 + 1);
    add(total / 2 - 1);
    add(total / 4);
    add(total / 4 + 1);
    add(total / 4 - 1);
    add(3 * total / 4);
    add(3 * total / 4 + 1);
    add(3 * total / 4 - 1);

    // powers of two and neighbors
    for (long long p = 1; p <= total; p <<= 1) {
        add(p);
        add(p - 1);
        add(p + 1);
    }

    // deduplicate specials
    sort(special.begin(), special.end());
    special.erase(unique(special.begin(), special.end()), special.end());

    long long m;
    int mode = rnd.next(0, 2);
    if (mode == 0 || special.empty()) {
        // Completely random valid step
        m = rnd.next(1LL, total);
    } else if (mode == 1) {
        // Choose from special boundary/interesting values
        m = rnd.any(special);
    } else {
        // Mix: values near center plus specials
        if (rnd.next(0, 1) == 0) {
            m = rnd.any(special);
        } else {
            long long center = total / 2;
            long long left = max(1LL, center - 10);
            long long right = min(total, center + 10);
            if (left > right) left = right;
            m = rnd.next(left, right);
        }
    }

    println(n, m);
    return 0;
}

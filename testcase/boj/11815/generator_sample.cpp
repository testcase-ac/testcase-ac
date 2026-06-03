#include "testlib.h"

#include <vector>
using namespace std;

long long square(long long x) {
    return x * x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    if (mode == 5) n = rnd.next(31, 100);

    vector<long long> values;
    values.reserve(n);

    vector<long long> anchors = {
        1LL,
        2LL,
        3LL,
        4LL,
        8LL,
        9LL,
        15LL,
        16LL,
        999999937LL,
        1000000000000000000LL,
        999999999999999999LL,
        999999999999999936LL,
    };

    while ((int)values.size() < n) {
        long long x;
        int choice = rnd.next(0, 99);

        if (mode == 0 || choice < 20) {
            x = rnd.any(anchors);
        } else if (mode == 1 || choice < 45) {
            long long root = rnd.next(1LL, 1000000000LL);
            x = square(root);
        } else if (mode == 2 || choice < 70) {
            long long root = rnd.next(1LL, 999999999LL);
            long long delta = rnd.any(vector<long long>{-2LL, -1LL, 1LL, 2LL});
            x = square(root) + delta;
            if (x < 1) x = 2;
        } else if (mode == 3 || choice < 85) {
            long long hi = 1000000000000000000LL;
            x = hi - rnd.next(0LL, 1000000LL);
        } else {
            x = rnd.next(1LL, 1000000000000000000LL);
        }

        values.push_back(x);
    }

    shuffle(values.begin(), values.end());
    println(n);
    println(values);

    return 0;
}

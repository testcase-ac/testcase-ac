#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<long long> boards;

    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = 4;
    } else if (mode == 2) {
        n = rnd.next(5, 10);
    } else {
        n = rnd.next(11, 30);
    }

    boards.reserve(n);

    if (mode == 3) {
        long long base = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            boards.push_back(max(1LL, base - rnd.next(0, 5)));
        }
    } else if (mode == 4) {
        int small = rnd.next(1, 20);
        int large = rnd.next(900000000, 1000000000);
        for (int i = 0; i < n; ++i) {
            boards.push_back((i % 3 == 0) ? large : rnd.next(1, small));
        }
    } else {
        long long hi = rnd.any(vector<long long>{10LL, 100LL, 1000000000LL});
        for (int i = 0; i < n; ++i) {
            boards.push_back(rnd.next(1LL, hi));
        }
    }

    if (mode == 5) {
        sort(boards.begin(), boards.end());
    } else if (mode == 6) {
        sort(boards.rbegin(), boards.rend());
    } else {
        shuffle(boards.begin(), boards.end());
    }

    println(n);
    println(boards);

    return 0;
}

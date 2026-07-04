#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int evenInRange(int lo, int hi) {
    lo += lo % 2;
    hi -= hi % 2;
    return rnd.next(lo / 2, hi / 2) * 2;
}

vector<int> makeDataset(int mode) {
    if (mode == 0) {
        return {evenInRange(2, 1000000)};
    }

    if (mode == 1) {
        int first = evenInRange(2, 80);
        int second = evenInRange(max(2, first - 20), min(1000000, first + 80));
        return {first, second};
    }

    if (mode == 2) {
        int base = evenInRange(2, 120);
        vector<int> voters = {
            base,
            evenInRange(2, 140),
            evenInRange(2, 40),
            evenInRange(80, 220),
            evenInRange(40, 160),
        };
        if (rnd.next(2)) voters.back() += 2;
        return voters;
    }

    int n = rnd.next(3, 12);
    vector<int> voters(n);

    if (mode == 3) {
        int start = evenInRange(2, 60);
        int step = evenInRange(2, 40);
        for (int i = 0; i < n; ++i) {
            voters[i] = min(1000000, start + i * step);
            voters[i] -= voters[i] % 2;
        }
        if (rnd.next(2)) reverse(voters.begin(), voters.end());
        return voters;
    }

    if (mode == 4) {
        voters[0] = evenInRange(2, 1000000);
        for (int i = 1; i < n; ++i) {
            voters[i] = rnd.next(3) == 0 ? 1000000 : evenInRange(2, 200);
        }
        shuffle(voters.begin() + 1, voters.end());
        return voters;
    }

    int lo = evenInRange(2, 200);
    int hi = evenInRange(lo, min(1000000, lo + rnd.next(20, 500)));
    for (int i = 0; i < n; ++i) {
        voters[i] = evenInRange(lo, hi);
    }
    return voters;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(1, 8);
    println(k);
    for (int dataset = 0; dataset < k; ++dataset) {
        vector<int> voters = makeDataset(rnd.next(0, 5));
        println((int)voters.size());
        for (int value : voters) {
            println(value);
        }
    }

    return 0;
}

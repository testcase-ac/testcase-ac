#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> subsetSums(const vector<int>& tribute) {
    vector<int> sums;
    int n = (int)tribute.size();
    sums.reserve((1 << n) - 1);
    for (int mask = 1; mask < (1 << n); ++mask) {
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                sum += tribute[i];
            }
        }
        sums.push_back((int)sum);
    }
    shuffle(sums.begin(), sums.end());
    return sums;
}

vector<int> randomPositiveList(int n, int maxValue) {
    vector<int> sums((1 << n) - 1);
    for (int& value : sums) {
        value = rnd.next(1, maxValue);
    }
    return sums;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(3, 8);
    println(z);

    for (int tc = 0; tc < z; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        vector<int> sums;

        if (mode == 0) {
            n = 1;
            int value = rnd.next(0, 3) == 0 ? rnd.next(1999999900, 2000000000)
                                             : rnd.next(1, 100);
            sums = {value};
        } else if (mode == 1) {
            n = rnd.next(2, 7);
            vector<int> tribute(n);
            int base = rnd.next(1, 8);
            for (int i = 0; i < n; ++i) {
                tribute[i] = base + rnd.next(0, 3);
            }
            sums = subsetSums(tribute);
        } else if (mode == 2) {
            n = rnd.next(2, 7);
            vector<int> tribute(n);
            tribute[0] = rnd.next(1, 5);
            for (int i = 1; i < n; ++i) {
                tribute[i] = tribute[i - 1] + rnd.next(1, 6);
            }
            sums = subsetSums(tribute);
        } else if (mode == 3) {
            n = rnd.next(2, 6);
            vector<int> tribute(n);
            for (int i = 0; i < n; ++i) {
                tribute[i] = rnd.next(1, 20);
            }
            sums = subsetSums(tribute);
            int idx = rnd.next((int)sums.size());
            sums[idx] = rnd.next(1, 120);
            shuffle(sums.begin(), sums.end());
        } else if (mode == 4) {
            n = rnd.next(2, 7);
            sums = randomPositiveList(n, 80);
            sort(sums.begin(), sums.end());
            if (rnd.next(0, 1)) {
                shuffle(sums.begin(), sums.end());
            }
        } else {
            n = rnd.next(2, 5);
            vector<int> tribute(n, rnd.next(1, 10));
            sums = subsetSums(tribute);
            for (int i = 0; i < rnd.next(1, 3); ++i) {
                int idx = rnd.next((int)sums.size());
                sums[idx] = min(2000000000, sums[idx] + rnd.next(1, 5));
            }
            shuffle(sums.begin(), sums.end());
        }

        println(n);
        println(sums);
    }

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<int> ranks(n);
    iota(ranks.begin(), ranks.end(), 1);

    if (mode == 0) {
        // Already sorted final ranks.
    } else if (mode == 1) {
        reverse(ranks.begin(), ranks.end());
    } else if (mode == 2) {
        int shift = rnd.next(0, n - 1);
        rotate(ranks.begin(), ranks.begin() + shift, ranks.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int pos = rnd.next(0, max(0, n - 2));
            swap(ranks[pos], ranks[pos + 1]);
        }
    } else if (mode == 4) {
        int left = rnd.next(0, n - 1);
        int right = rnd.next(left, n - 1);
        reverse(ranks.begin() + left, ranks.begin() + right + 1);
    } else {
        shuffle(ranks.begin(), ranks.end());
    }

    println(n);
    println(ranks);

    return 0;
}

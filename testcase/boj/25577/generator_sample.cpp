#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<long long> makeValues(int n, bool useExtremes) {
    set<long long> seen;
    vector<long long> values;

    if (useExtremes) {
        values.push_back(-1000000000LL);
        values.push_back(1000000000LL);
        seen.insert(values[0]);
        seen.insert(values[1]);
    }

    while ((int)values.size() < n) {
        long long x = rnd.next(-1000000000LL, 1000000000LL);
        if (seen.insert(x).second) {
            values.push_back(x);
        }
    }

    sort(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(4, mode == 2 ? 40 : 24);
    vector<long long> a = makeValues(n, rnd.next(0, 4) == 0);

    if (mode == 0) {
        // Already sorted.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int p = rnd.next(0, n - 2);
            swap(a[p], a[p + 1]);
        }
    } else if (mode == 4) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, n - 1);
            if (x != y) {
                swap(a[x], a[y]);
            }
        }
    } else {
        int shift = rnd.next(1, n - 1);
        rotate(a.begin(), a.begin() + shift, a.end());
    }

    println(n);
    println(a);
    return 0;
}

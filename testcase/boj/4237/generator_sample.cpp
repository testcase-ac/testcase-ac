#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> values(n);
    iota(values.begin(), values.end(), 1);
    return values;
}

vector<int> alternatingExtremes(int n, bool highFirst) {
    vector<int> values;
    int lo = 1;
    int hi = n;
    while (lo <= hi) {
        if (highFirst) {
            values.push_back(hi--);
            if (lo <= hi) values.push_back(lo++);
        } else {
            values.push_back(lo++);
            if (lo <= hi) values.push_back(hi--);
        }
    }
    return values;
}

vector<int> blockPermutation(int n, int blockSize, bool reverseBlocks) {
    vector<int> values = identityPermutation(n);
    for (int start = 0; start < n; start += blockSize) {
        int finish = min(n, start + blockSize);
        if (reverseBlocks) {
            reverse(values.begin() + start, values.begin() + finish);
        } else {
            shuffle(values.begin() + start, values.begin() + finish);
        }
    }
    return values;
}

vector<int> nearlyMonotone(int n, bool descending) {
    vector<int> values = identityPermutation(n);
    if (descending) reverse(values.begin(), values.end());

    int swaps = rnd.next(1, max(1, min(n - 1, 5)));
    for (int i = 0; i < swaps; ++i) {
        int left = rnd.next(0, n - 1);
        int right = rnd.next(max(0, left - 2), min(n - 1, left + 2));
        swap(values[left], values[right]);
    }

    return values;
}

vector<int> makeCase(int n) {
    if (n == 1) return identityPermutation(n);

    int mode = rnd.next(0, 6);
    if (mode == 0) return identityPermutation(n);
    if (mode == 1) {
        vector<int> values = identityPermutation(n);
        reverse(values.begin(), values.end());
        return values;
    }
    if (mode == 2) return alternatingExtremes(n, rnd.next(0, 1) == 1);
    if (mode == 3) return blockPermutation(n, rnd.next(2, min(n, 7)), rnd.next(0, 1) == 1);
    if (mode == 4) return nearlyMonotone(n, false);
    if (mode == 5) return nearlyMonotone(n, true);

    vector<int> values = identityPermutation(n);
    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = 2;
        } else if (rnd.next(0, 9) == 0) {
            n = rnd.next(25, 80);
        } else {
            n = rnd.next(3, 20);
        }

        vector<int> values = makeCase(n);
        cout << n;
        for (int value : values) cout << ' ' << value;
        cout << '\n';
    }

    return 0;
}

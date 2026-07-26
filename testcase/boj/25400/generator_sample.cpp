#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 30);
    int mode = rnd.next(0, 3);
    vector<int> a(n);

    if (mode == 0) {
        for (int& x : a) x = rnd.next(1, n + 3);
    } else if (mode == 1) {
        int k = rnd.next(1, n);
        for (int& x : a) x = rnd.next(k + 1, k + 10);
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        positions.resize(k);
        sort(positions.begin(), positions.end());
        for (int i = 0; i < k; ++i) a[positions[i]] = i + 1;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = i % 3 == 0 ? 1 : rnd.next(2, n + 3);
    } else {
        for (int i = 0; i < n; ++i) a[i] = i + 1;
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
}

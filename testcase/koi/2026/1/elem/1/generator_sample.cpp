#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 25);
    int k1 = rnd.next(1, n - 1);
    int k2 = rnd.next(1, n - 1);
    int mode = rnd.next(0, 4);
    vector<int> school(n);

    if (mode == 0) {
        fill(school.begin(), school.end(), rnd.next(1, 2));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) school[i] = i % 2 + 1;
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) school[i] = i < split ? 1 : 2;
    } else {
        for (int& value : school) value = rnd.next(1, 2);
    }

    if (mode == 4) {
        k1 = rnd.next(0, 1) ? 1 : n - 1;
        k2 = rnd.next(0, 1) ? 1 : n - 1;
    }

    println(n, k1, k2);
    println(school);
}

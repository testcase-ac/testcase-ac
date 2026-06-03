#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

const int64 MAX_N = 1000000000000000000LL;

int64 withResidue(int residue) {
    int64 maxK = (MAX_N - residue) / 9;
    int64 k = rnd.wnext(maxK + 1, -2);
    int64 value = k * 9 + residue;
    if (value < 1) value += 9;
    return value;
}

int64 nearLimit() {
    int64 delta = rnd.next(0, 200);
    return rnd.next(0, 1) == 0 ? 1 + delta : MAX_N - delta;
}

int64 randomN() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return rnd.next(1, 80);
    if (mode == 1) return nearLimit();
    if (mode == 2) return withResidue(rnd.next(0, 8));
    if (mode == 3) return rnd.next(1LL, 1000000LL);
    return rnd.next(1LL, MAX_N);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int t;
    vector<int64> values;

    if (mode == 0) {
        t = rnd.next(1, 20);
        for (int i = 0; i < t; ++i) values.push_back(rnd.next(1, 120));
    } else if (mode == 1) {
        t = rnd.next(9, 45);
        for (int i = 0; i < t; ++i) values.push_back(withResidue(i % 9));
    } else if (mode == 2) {
        t = rnd.next(2, 30);
        for (int i = 0; i < t; ++i) values.push_back(nearLimit());
    } else if (mode == 3) {
        t = 1000;
        for (int i = 0; i < t; ++i) values.push_back(randomN());
    } else {
        t = rnd.next(1, 1000);
        for (int i = 0; i < t; ++i) values.push_back(randomN());
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int64 value : values) println(value);

    return 0;
}

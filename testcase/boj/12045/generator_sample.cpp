#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

const int MAX_VALUE = 1000000000;

int randomValue() {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return rnd.next(0, 15);
    }
    if (mode == 1) {
        return rnd.next(0, 1023);
    }
    if (mode == 2) {
        return rnd.next(MAX_VALUE - 1024, MAX_VALUE);
    }
    if (mode == 3) {
        vector<int> values = {0, 1, 2, 3, 7, 15, 255, 1023, MAX_VALUE};
        return rnd.any(values);
    }
    return rnd.next(0, MAX_VALUE);
}

vector<int> makeList(int n, int paletteSize) {
    vector<int> palette;
    for (int i = 0; i < paletteSize; ++i) {
        palette.push_back(randomValue());
    }

    vector<int> values;
    for (int i = 0; i < n; ++i) {
        if (!palette.empty() && rnd.next(0, 99) < 75) {
            values.push_back(rnd.any(palette));
        } else {
            values.push_back(randomValue());
        }
    }
    return values;
}

vector<int> makeLowList(int n, int paletteSize) {
    vector<int> palette;
    for (int i = 0; i < paletteSize; ++i) {
        palette.push_back(rnd.next(0, 1023));
    }

    vector<int> values;
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 99) < 80) {
            values.push_back(rnd.any(palette));
        } else {
            values.push_back(rnd.next(0, 1023));
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(1, mode == 4 ? 30 : 12);
        int k = randomValue();

        array<vector<int>, 4> lists;
        if (mode == 0) {
            for (int i = 0; i < 4; ++i) {
                lists[i].assign(n, rnd.next(0, 1) ? 0 : k);
            }
        } else if (mode == 1) {
            int paletteSize = rnd.next(1, min(n, 4));
            for (int i = 0; i < 4; ++i) {
                lists[i] = makeList(n, paletteSize);
            }
        } else if (mode == 2) {
            k = rnd.next(0, 1023);
            vector<int> a = makeLowList(n, rnd.next(1, min(n, 4)));
            vector<int> b = makeLowList(n, rnd.next(1, min(n, 4)));
            vector<int> c = makeLowList(n, rnd.next(1, min(n, 4)));
            vector<int> d;
            for (int i = 0; i < n; ++i) {
                int target = a[rnd.next(n)] ^ b[rnd.next(n)] ^ c[rnd.next(n)] ^ k;
                d.push_back(target);
            }
            lists = {a, b, c, d};
        } else if (mode == 3) {
            for (int i = 0; i < 4; ++i) {
                lists[i].clear();
                for (int j = 0; j < n; ++j) {
                    lists[i].push_back(rnd.next(0, 1) ? 0 : MAX_VALUE);
                }
            }
            k = rnd.next(0, 1) ? 0 : MAX_VALUE;
        } else {
            for (int i = 0; i < 4; ++i) {
                lists[i] = makeList(n, rnd.next(1, min(n, 8)));
                shuffle(lists[i].begin(), lists[i].end());
            }
        }

        println(n, k);
        for (int i = 0; i < 4; ++i) {
            println(lists[i]);
        }
    }

    return 0;
}

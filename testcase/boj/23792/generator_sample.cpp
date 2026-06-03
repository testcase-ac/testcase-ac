#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {
constexpr int MAX_TASTE = 2147483647;

void printVector(const vector<int>& values) {
    println(values);
}

vector<vector<int>> buildTasteArrays(int n) {
    int mode = rnd.next(0, 3);
    vector<int> all;
    all.reserve(3 * n);

    if (mode == 0) {
        int value = rnd.next(1, 20);
        for (int i = 0; i < 3 * n; ++i) {
            value += rnd.next(1, 3);
            all.push_back(value);
        }
        shuffle(all.begin(), all.end());
    } else if (mode == 1) {
        int gap = rnd.next(1000, 3000);
        int starts[3] = {rnd.next(1, 20), rnd.next(1, 20) + gap,
                         rnd.next(1, 20) + 2 * gap};
        for (int group = 0; group < 3; ++group) {
            int value = starts[group];
            for (int i = 0; i < n; ++i) {
                value += rnd.next(1, 4);
                all.push_back(value);
            }
        }
    } else if (mode == 2) {
        int value = rnd.next(1, 100);
        for (int i = 0; i < 3 * n; ++i) {
            value += rnd.next(1, 25);
            all.push_back(value);
        }
        shuffle(all.begin(), all.end());
    } else {
        int value = MAX_TASTE - rnd.next(10000, 30000);
        for (int i = 0; i < 3 * n; ++i) {
            value += rnd.next(1, 9);
            all.push_back(value);
        }
        shuffle(all.begin(), all.end());
    }

    vector<vector<int>> taste(3);
    for (int group = 0; group < 3; ++group) {
        taste[group].reserve(n);
    }
    for (int i = 0; i < 3 * n; ++i) {
        taste[i % 3].push_back(all[i]);
    }
    for (int group = 0; group < 3; ++group) {
        sort(taste[group].begin(), taste[group].end());
    }
    return taste;
}
}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n = 1;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 5);
    } else if (sizeMode == 2) {
        n = rnd.next(6, 12);
    } else if (sizeMode == 3) {
        n = rnd.next(13, 25);
    } else {
        n = rnd.next(40, 80);
    }

    vector<vector<int>> taste = buildTasteArrays(n);

    int q = rnd.next(1, min(25, max(1, 2 * n)));

    println(n);
    printVector(taste[0]);
    printVector(taste[1]);
    printVector(taste[2]);
    println(q);

    for (int i = 0; i < q; ++i) {
        int x, y, z;
        if (i == 0) {
            x = y = z = n;
        } else if (rnd.next(0, 3) == 0) {
            x = rnd.next(1, min(n, 3));
            y = rnd.next(1, min(n, 3));
            z = rnd.next(1, min(n, 3));
        } else {
            x = rnd.next(1, n);
            y = rnd.next(1, n);
            z = rnd.next(1, n);
        }

        int total = x + y + z;
        int kMode = rnd.next(0, 4);
        int k = 1;
        if (kMode == 0) {
            k = 1;
        } else if (kMode == 1) {
            k = total;
        } else if (kMode == 2) {
            k = rnd.next(1, min(total, 3));
        } else if (kMode == 3) {
            k = rnd.next(max(1, total - 2), total);
        } else {
            k = rnd.next(1, total);
        }

        println(x, y, z, k);
    }

    return 0;
}

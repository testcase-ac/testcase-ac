#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> makePositiveParts(int n, int total, int mode) {
    vector<int> values(n, 1);
    int remaining = total - n;

    if (mode == 0) {
        values[rnd.next(n)] += remaining;
        return values;
    }

    for (int i = 0; i < remaining; ++i) {
        int idx = rnd.next(n);
        if (mode == 1) {
            idx = rnd.wnext(n, 2);
        } else if (mode == 2) {
            idx = rnd.wnext(n, -2);
        }
        ++values[idx];
    }

    return values;
}

vector<int> makeNonnegativeParts(int n, int total, int mode) {
    if (n == 1) {
        return vector<int>{total};
    }

    vector<int> values(n, 0);
    if (mode == 0) {
        values[rnd.next(n)] = total;
        return values;
    }

    int active = rnd.next(1, n);
    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0);
    shuffle(indices.begin(), indices.end());

    vector<int> positive = makePositiveParts(active, total, mode % 3);
    for (int i = 0; i < active; ++i) {
        values[indices[i]] = positive[i];
    }
    return values;
}

void printProbabilityLine(const vector<int>& values) {
    for (int i = 0; i < int(values.size()); ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d.%06d", values[i] / 1000000, values[i] % 1000000);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(4);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 8);
    } else if (sizeMode == 2) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(31, 80);
    }

    int qMode = rnd.next(4);
    int rMode = rnd.next(4);

    vector<int> q = makeNonnegativeParts(n, 1000000, qMode);
    vector<int> r = makePositiveParts(n, 1000000, rMode);

    println(n);
    printProbabilityLine(q);
    printProbabilityLine(r);

    return 0;
}

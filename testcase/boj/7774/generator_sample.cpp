#include "testlib.h"

#include <vector>

using namespace std;

static vector<int> randomValues(int count, int mode) {
    vector<int> values;
    values.reserve(count);

    for (int i = 0; i < count; ++i) {
        int value;
        if (mode == 0) {
            value = rnd.next(1, 4);
        } else if (mode == 1) {
            value = rnd.next(1, 20);
        } else if (mode == 2) {
            value = rnd.next(900, 1000);
        } else {
            value = rnd.next(1, 1000);
        }
        values.push_back(value);
    }

    return values;
}

static void printLine(const vector<int>& values) {
    if (values.empty()) {
        printf("\n");
    } else {
        println(values);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int m;

    if (mode == 0) {
        n = 0;
        m = rnd.next(0, 8);
    } else if (mode == 1) {
        n = rnd.next(0, 8);
        m = 0;
    } else if (mode == 2) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else if (mode == 3) {
        n = rnd.next(1, 3);
        m = rnd.next(8, 18);
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        m = rnd.next(1, 3);
    } else if (mode == 5) {
        n = rnd.next(10, 30);
        m = rnd.next(10, 30);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
    }

    int valueMode = rnd.next(0, 3);
    vector<int> a = randomValues(n, valueMode);
    vector<int> b = randomValues(m, rnd.next(0, 3));

    if (rnd.next(0, 1)) {
        shuffle(a.begin(), a.end());
    }
    if (rnd.next(0, 1)) {
        shuffle(b.begin(), b.end());
    }

    println(n, m);
    printLine(a);
    printLine(b);

    return 0;
}

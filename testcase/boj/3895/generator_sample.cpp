#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Row {
    int n;
    int k;
    int m;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Row> rows;

    rows.push_back({2, rnd.next(1, 3), rnd.next(1, 2)});
    rows.push_back({3, rnd.next(1, 6), rnd.next(1, 3)});

    int smallCount = rnd.next(8, 16);
    for (int i = 0; i < smallCount; ++i) {
        int n = rnd.next(2, 20);
        int mode = rnd.next(5);
        int k;
        if (mode == 0) {
            k = 1;
        } else if (mode == 1) {
            k = n;
        } else if (mode == 2) {
            k = n + rnd.next(1, 20);
        } else if (mode == 3) {
            k = rnd.next(9000, 10000);
        } else {
            k = rnd.next(1, 10000);
        }
        int m = rnd.next(1, n);
        rows.push_back({n, k, m});
    }

    int mediumCount = rnd.next(4, 10);
    for (int i = 0; i < mediumCount; ++i) {
        int n = rnd.next(21, 250);
        int k = rnd.next(1, 10000);
        int edge = rnd.next(4);
        int m = edge == 0 ? 1 : edge == 1 ? n : rnd.next(1, n);
        rows.push_back({n, k, m});
    }

    int largeCount = rnd.next(2, 5);
    for (int i = 0; i < largeCount; ++i) {
        int n = rnd.next(1000, 10000);
        int k = rnd.next(8000, 10000);
        int edge = rnd.next(5);
        int m = edge == 0 ? 1 : edge == 1 ? n : rnd.next(1, n);
        rows.push_back({n, k, m});
    }

    rows.push_back({10000, 10000, rnd.next(1, 10000)});
    rows.push_back({rnd.next(2, 10000), 1, 1});

    shuffle(rows.begin(), rows.end());
    if ((int)rows.size() > 99) {
        rows.resize(99);
    }

    for (const Row& row : rows) {
        println(row.n, row.k, row.m);
    }
    println(0, 0, 0);

    return 0;
}

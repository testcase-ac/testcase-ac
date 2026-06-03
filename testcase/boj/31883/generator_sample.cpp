#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Row {
    int a;
    int b;
    int c;
    int d;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
    } else {
        n = rnd.next(8, 20);
    }

    vector<Row> rows;
    rows.reserve(n);

    for (int i = 0; i < n; ++i) {
        Row row;
        if (mode == 0) {
            row.a = rnd.next(1, 5);
            row.b = rnd.next(row.a + 1, min(100, row.a + 5));
            row.c = rnd.next(1, 6);
            row.d = rnd.next(1, 6);
        } else if (mode == 1) {
            row.a = rnd.next(1, 10);
            row.b = rnd.next(80, 100);
            row.c = rnd.any(vector<int>{1, 2, 3, 100});
            row.d = rnd.any(vector<int>{1, 2, 3, 100});
        } else if (mode == 2) {
            row.a = rnd.next(1, 99);
            row.b = row.a + 1;
            row.c = rnd.next(1, 4);
            row.d = rnd.next(60, 100);
        } else if (mode == 3) {
            row.a = rnd.next(70, 99);
            row.b = rnd.next(row.a + 1, 100);
            row.c = rnd.next(60, 100);
            row.d = rnd.next(1, 4);
        } else if (mode == 4) {
            row.a = rnd.next(1, 20);
            row.b = rnd.next(row.a + 1, 100);
            row.c = rnd.next(1, 100);
            row.d = rnd.next(1, 100);
        } else {
            int base = rnd.next(1, 8);
            row.a = base;
            row.b = rnd.next(base + 1, min(100, base + rnd.next(1, 20)));
            row.c = rnd.any(vector<int>{1, 2, 5, 10, 25, 50, 100});
            row.d = rnd.any(vector<int>{1, 2, 5, 10, 25, 50, 100});
        }
        rows.push_back(row);
    }

    if (rnd.next(2) == 1) {
        shuffle(rows.begin(), rows.end());
    }

    println(n);
    for (const Row& row : rows) {
        println(row.a, row.b, row.c, row.d);
    }

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(6, 12);
    } else if (mode == 2) {
        n = rnd.next(8, 20);
    } else if (mode == 3) {
        n = rnd.next(15, 35);
    } else if (mode == 4) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(2, 25);
    }

    int distinct;
    if (mode == 0) {
        distinct = rnd.next(1, n);
    } else if (mode == 1) {
        distinct = n;
    } else if (mode == 2) {
        distinct = rnd.next(1, max(1, n / 3));
    } else if (mode == 3) {
        distinct = rnd.next(max(1, n / 2), n);
    } else if (mode == 4) {
        distinct = rnd.next(2, min(n, 20));
    } else {
        distinct = rnd.next(1, n);
    }

    vector<int> values;
    int valueMode = rnd.next(0, 3);
    int base = rnd.next(1, 100000);
    for (int i = 0; i < distinct; ++i) {
        int value;
        if (valueMode == 0) {
            value = i + 1;
        } else if (valueMode == 1) {
            value = 100000 - i;
        } else if (valueMode == 2) {
            value = 1 + i * rnd.next(2, 13);
        } else {
            value = 1 + ((base + i * 9973) % 100000);
        }
        values.push_back(value);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    distinct = (int)values.size();

    vector<int> a = values;
    while ((int)a.size() < n) {
        int id;
        if (mode == 2) {
            id = rnd.wnext(distinct, -2);
        } else if (mode == 4) {
            id = rnd.wnext(distinct, 3);
        } else {
            id = rnd.next(distinct);
        }
        a.push_back(values[id]);
    }

    if (mode == 5) {
        sort(a.begin(), a.end());
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else {
        shuffle(a.begin(), a.end());
    }

    int m;
    int mMode = rnd.next(0, 3);
    if (mMode == 0) {
        m = 1;
    } else if (mMode == 1) {
        m = distinct;
    } else if (mMode == 2) {
        m = rnd.next(1, distinct);
    } else {
        m = max(1, distinct - rnd.next(0, min(3, distinct - 1)));
    }

    println(n, m);
    println(a);

    return 0;
}

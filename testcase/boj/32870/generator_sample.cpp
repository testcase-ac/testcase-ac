#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 300000;

int clampValue(int x) {
    return max(0, min(MAX_A, x));
}

int randomNearMultiple(int m) {
    int k = rnd.next(0, MAX_A / m);
    int offset = rnd.next(-2, 2);
    return clampValue(k * m + offset);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, mode == 0 ? 6 : 24);
    int q = rnd.next(1, 24);

    vector<int> a;
    vector<int> queries;

    if (mode == 0) {
        n = rnd.next(1, 5);
        vector<int> pool = {0, 1, 2, 299999, 300000};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
        queries = {1, 2, 3, 299999, 300000};
    } else if (mode == 1) {
        int m = rnd.next(2, 80);
        n = rnd.next(6, 22);
        for (int i = 0; i < n; ++i) {
            a.push_back(randomNearMultiple(m));
        }
        queries = {1, m, max(1, m - 1), min(MAX_A, m + 1), rnd.next(2, 300)};
    } else if (mode == 2) {
        int base = rnd.next(0, MAX_A);
        n = rnd.next(8, 24);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-5, 5);
            a.push_back(clampValue(base + delta));
        }
        queries = {1, 2, 5, 10, rnd.next(11, 1000)};
    } else if (mode == 3) {
        n = rnd.next(8, 24);
        int step = rnd.next(1, 20000);
        int start = rnd.next(0, step - 1);
        for (int i = 0; i < n; ++i) {
            a.push_back((start + i * step) % (MAX_A + 1));
        }
        queries = {1, step, min(MAX_A, step + 1), rnd.next(2, 5000)};
    } else {
        n = rnd.next(10, 25);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(rnd.any(vector<int>{0, 1, 299999, 300000}));
            } else {
                a.push_back(rnd.next(0, MAX_A));
            }
        }
        queries = {1, 2, 7, 997, 300000};
    }

    while ((int)queries.size() < q) {
        int choice = rnd.next(0, 4);
        if (choice == 0) {
            queries.push_back(rnd.next(1, 20));
        } else if (choice == 1) {
            queries.push_back(rnd.next(21, 1000));
        } else if (choice == 2) {
            queries.push_back(rnd.next(1001, 300000));
        } else {
            int x = rnd.any(a);
            queries.push_back(clampValue(x + rnd.next(-3, 3)));
            if (queries.back() == 0) {
                queries.back() = 1;
            }
        }
    }
    shuffle(a.begin(), a.end());
    shuffle(queries.begin(), queries.end());

    println(n, q);
    println(a);
    for (int i = 0; i < q; ++i) {
        println(queries[i]);
    }

    return 0;
}

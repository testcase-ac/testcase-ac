#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    vector<int> a(n);
    vector<pair<int, int>> focusedQueries;

    if (mode == 0) {
        int value = rnd.next(1, 100000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int distinct = rnd.next(1, min(n, 8));
        for (int i = 0; i < n; ++i) {
            a[i] = 1 + i % distinct;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 20);
        }

        int len = rnd.next(1, n);
        int left = rnd.next(0, n - len);
        for (int offset = 0; offset < len / 2; ++offset) {
            a[left + len - 1 - offset] = a[left + offset];
        }
        focusedQueries.emplace_back(left + 1, left + len);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? rnd.next(1, 4) : rnd.next(5, 8));
        }
    } else if (mode == 4) {
        int start = rnd.next(1, 100000 - n + 1);
        for (int i = 0; i < n; ++i) {
            a[i] = start + i;
        }
        shuffle(a.begin(), a.end());
    } else {
        int alphabet = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, alphabet);
        }
    }

    focusedQueries.emplace_back(1, 1);
    focusedQueries.emplace_back(n, n);
    focusedQueries.emplace_back(1, n);
    if (n >= 2) {
        focusedQueries.emplace_back(1, 2);
        focusedQueries.emplace_back(n - 1, n);
    }

    int m = rnd.next(1, 60);
    vector<pair<int, int>> queries;
    for (auto query : focusedQueries) {
        if (query.first <= query.second && query.second <= n) {
            queries.push_back(query);
        }
    }

    while ((int)queries.size() < m) {
        int s = rnd.next(1, n);
        int e = rnd.next(s, n);
        queries.emplace_back(s, e);
    }

    shuffle(queries.begin(), queries.end());

    println(n);
    println(a);
    println((int)queries.size());
    for (auto [s, e] : queries) {
        println(s, e);
    }

    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int pickRank(int total) {
    int mode = rnd.next(6);
    if (mode == 0) return 1;
    if (mode == 1) return total;
    if (mode == 2) return (total + 1) / 2;
    return rnd.next(1, total);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_TASTE = 2147483647LL;

    int sizeMode = rnd.next(5);
    int n;
    if (sizeMode == 0)
        n = 1;
    else if (sizeMode <= 2)
        n = rnd.next(2, 8);
    else if (sizeMode == 3)
        n = rnd.next(9, 25);
    else
        n = rnd.next(26, 60);

    int pattern = rnd.next(5);
    vector<long long> a, b;
    a.reserve(n);
    b.reserve(n);

    if (pattern == 0) {
        for (int x = 1; x <= 2 * n; ++x) {
            if (x % 2 == 1)
                a.push_back(x);
            else
                b.push_back(x);
        }
    } else if (pattern == 1) {
        for (int x = 1; x <= n; ++x) a.push_back(x);
        long long cur = 1000;
        for (int x = 1; x <= n; ++x) {
            cur += rnd.next(1, 4);
            b.push_back(cur);
        }
    } else if (pattern == 2) {
        for (int x = 1; x <= n; ++x) b.push_back(x);
        long long cur = 1000;
        for (int x = 1; x <= n; ++x) {
            cur += rnd.next(1, 4);
            a.push_back(cur);
        }
    } else if (pattern == 3) {
        vector<long long> values;
        long long cur = rnd.next(1, 20);
        for (int x = 0; x < 2 * n; ++x) {
            cur += rnd.next(1, 30);
            values.push_back(cur);
        }
        vector<int> owner(2 * n, 0);
        for (int x = n; x < 2 * n; ++x) owner[x] = 1;
        shuffle(owner.begin(), owner.end());
        for (int x = 0; x < 2 * n; ++x) {
            if (owner[x] == 0)
                a.push_back(values[x]);
            else
                b.push_back(values[x]);
        }
    } else {
        vector<long long> values;
        long long start = MAX_TASTE - 2LL * n * 3LL + 1;
        for (int x = 0; x < 2 * n; ++x) values.push_back(start + 3LL * x);
        vector<int> owner(2 * n, 0);
        for (int x = n; x < 2 * n; ++x) owner[x] = 1;
        shuffle(owner.begin(), owner.end());
        for (int x = 0; x < 2 * n; ++x) {
            if (owner[x] == 0)
                a.push_back(values[x]);
            else
                b.push_back(values[x]);
        }
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int q = rnd.next(1, min(80, 4 * n + 10));
    vector<vector<int>> queries;
    queries.reserve(q);

    vector<pair<int, int>> prefixChoices = {
        {1, 1},
        {n, n},
        {rnd.next(1, n), 1},
        {1, rnd.next(1, n)},
        {rnd.next(1, n), rnd.next(1, n)},
    };
    shuffle(prefixChoices.begin(), prefixChoices.end());

    for (auto [i, j] : prefixChoices) {
        if ((int)queries.size() == q) break;
        queries.push_back({i, j, pickRank(i + j)});
    }

    while ((int)queries.size() < q) {
        int i = rnd.next(1, n);
        int j = rnd.next(1, n);
        queries.push_back({i, j, pickRank(i + j)});
    }

    println(n);
    println(a);
    println(b);
    println(q);
    for (const auto& query : queries) println(query);

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "COW";
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 45 : 30);

    string s;
    if (mode == 0) {
        char ch = rnd.any(alphabet);
        s.assign(n, ch);
    } else if (mode == 1) {
        int offset = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) s += alphabet[(i + offset) % 3];
    } else if (mode == 2) {
        char a = rnd.any(alphabet);
        char b = rnd.any(alphabet);
        while (b == a) b = rnd.any(alphabet);
        for (int i = 0; i < n; ++i) s += (rnd.next(0, 99) < 70 ? a : b);
    } else if (mode == 3) {
        vector<string> blocks = {"C", "O", "W", "CO", "OW", "CW", "COW"};
        while (static_cast<int>(s.size()) < n) s += rnd.any(blocks);
        s.resize(n);
    } else {
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    }

    int q = rnd.next(1, min(90, n * (n + 1) / 2 + 20));
    vector<pair<int, int>> queries;

    auto addQuery = [&](int l, int r) {
        if (static_cast<int>(queries.size()) < q) queries.emplace_back(l, r);
    };

    addQuery(1, n);
    addQuery(rnd.next(1, n), rnd.next(1, n));
    if (queries.back().first > queries.back().second) swap(queries.back().first, queries.back().second);

    while (static_cast<int>(queries.size()) < q) {
        int kind = rnd.next(0, 4);
        if (kind == 0) {
            int p = rnd.next(1, n);
            addQuery(p, p);
        } else if (kind == 1) {
            int len = rnd.next(1, min(n, 6));
            int l = rnd.next(1, n - len + 1);
            addQuery(l, l + len - 1);
        } else if (kind == 2) {
            int len = rnd.next(1, n);
            int l = rnd.next(1, n - len + 1);
            addQuery(l, l + len - 1);
        } else if (kind == 3) {
            int l = rnd.next(1, n);
            addQuery(l, n);
        } else {
            int r = rnd.next(1, n);
            addQuery(1, r);
        }
    }

    shuffle(queries.begin(), queries.end());

    println(s);
    println(q);
    for (auto [l, r] : queries) println(l, r);

    return 0;
}

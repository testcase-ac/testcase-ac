#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    string s;
    vector<pair<int, int>> interesting;

    if (mode == 0) {
        int pairs = rnd.next(1, 15);
        n = pairs * 2;
        for (int i = 0; i < pairs; ++i) {
            s += "()";
            interesting.emplace_back(2 * i + 1, 2 * i + 2);
        }
    } else if (mode == 1) {
        int pairs = rnd.next(1, 15);
        n = pairs * 2;
        s.append(pairs, '(');
        s.append(pairs, ')');
        interesting.emplace_back(1, n);
        if (pairs > 1) interesting.emplace_back(2, n - 1);
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? ')' : '(');
    } else if (mode == 3) {
        int left = rnd.next(1, 20);
        int right = rnd.next(1, 20);
        n = left + right;
        s.append(left, '(');
        s.append(right, ')');
        if (left == right) interesting.emplace_back(1, n);
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) s += rnd.any(string("()"));
    } else {
        int groups = rnd.next(1, 8);
        for (int g = 0; g < groups; ++g) {
            int kind = rnd.next(0, 2);
            int start = static_cast<int>(s.size()) + 1;
            if (kind == 0) {
                s += "()";
                interesting.emplace_back(start, start + 1);
            } else if (kind == 1) {
                s += "(())";
                interesting.emplace_back(start, start + 3);
            } else {
                s += rnd.any(string("()"));
            }
        }
        n = static_cast<int>(s.size());
    }

    int m = rnd.next(1, 40);
    vector<pair<int, int>> queries;
    queries.reserve(m);

    auto addQuery = [&](int l, int r) {
        if (1 <= l && l <= r && r <= n && static_cast<int>(queries.size()) < m) {
            queries.emplace_back(l, r);
        }
    };

    addQuery(1, n);
    int firstRandom = rnd.next(1, n);
    int secondRandom = rnd.next(1, n);
    if (firstRandom > secondRandom) swap(firstRandom, secondRandom);
    addQuery(firstRandom, secondRandom);
    for (auto [l, r] : interesting) addQuery(l, r);

    while (static_cast<int>(queries.size()) < m) {
        int style = rnd.next(0, 5);
        int l = rnd.next(1, n);
        int r = rnd.next(l, n);

        if (style == 0) {
            r = l;
        } else if (style == 1 && l < n) {
            r = l + 1;
        } else if (style == 2) {
            l = 1;
            r = rnd.next(1, n);
        } else if (style == 3) {
            r = n;
        } else if (style == 4 && r > l && (r - l + 1) % 2 == 0) {
            --r;
        }

        addQuery(l, r);
    }

    println(s);
    println(m);
    for (auto [l, r] : queries) println(l, r);

    return 0;
}

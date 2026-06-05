#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(4, 30);
    string s(n, 'A');
    vector<pair<int, int>> planted;

    auto fillDistractors = [&]() {
        const string letters = "ACDEFGHIJKLMNOPQSTUVWXYZ";
        for (int i = 0; i < n; ++i) s[i] = rnd.any(letters);
    };

    fillDistractors();

    if (mode == 0) {
        int a = rnd.next(0, n - 4);
        s[a] = 'R';
        s[a + 1] = 'R';
        s[a + 2] = 'B';
        s[a + 3] = 'B';
        planted.push_back({a, a + 3});
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) s[i] = (i % 2 == 0 ? 'R' : 'B');
    } else if (mode == 2) {
        int split = rnd.next(2, n - 2);
        for (int i = 0; i < split; ++i) s[i] = 'R';
        for (int i = split; i < n; ++i) s[i] = 'B';
        planted.push_back({split - 2, split + 1});
    } else if (mode == 3) {
        int rCount = rnd.next(0, 1);
        int bCount = rnd.next(0, 1);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < rCount; ++i) s[pos.back()] = 'R', pos.pop_back();
        for (int i = 0; i < bCount; ++i) s[pos.back()] = 'B', pos.pop_back();
    } else if (mode == 4) {
        int a = rnd.next(0, n - 4);
        s[a] = 'R';
        s[a + 1] = rnd.next(0, 1) ? 'B' : 'R';
        s[a + 2] = rnd.next(0, 1) ? 'R' : 'B';
        s[a + 3] = 'B';
    } else {
        const string letters = "ABR";
        for (int i = 0; i < n; ++i) s[i] = rnd.any(letters);
        int suffix = rnd.next(1, min(6, n));
        for (int i = n - suffix; i < n; ++i) s[i] = 'B';
    }

    int q = rnd.next(1, 20);
    vector<pair<int, int>> queries;

    auto addQuery = [&](int l, int r) {
        l = max(0, min(l, n - 1));
        r = max(0, min(r, n - 1));
        if (l > r) swap(l, r);
        queries.push_back({l, r});
    };

    addQuery(0, n - 1);
    for (auto interval : planted) addQuery(interval.first, interval.second);

    while ((int)queries.size() < q) {
        int queryMode = rnd.next(0, 4);
        if (queryMode == 0) {
            int l = rnd.next(0, n - 1);
            int len = rnd.next(0, min(5, n - 1 - l));
            addQuery(l, l + len);
        } else if (queryMode == 1) {
            int l = rnd.next(0, n - 4);
            addQuery(l, l + rnd.next(3, n - 1 - l));
        } else if (queryMode == 2 && !planted.empty()) {
            auto interval = rnd.any(planted);
            addQuery(interval.first + rnd.next(-1, 1), interval.second + rnd.next(-1, 1));
        } else if (queryMode == 3) {
            int r = rnd.next(0, n - 1);
            addQuery(0, r);
        } else {
            int l = rnd.next(0, n - 1);
            addQuery(l, n - 1);
        }
    }

    shuffle(queries.begin(), queries.end());

    println(n, q);
    println(s);
    for (int i = 0; i < q; ++i) println(queries[i].first, queries[i].second);

    return 0;
}

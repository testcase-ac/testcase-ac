#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

int valueOf(const string& s, int l, int r) {
    int value = 0;
    for (int i = l; i <= r; ++i) {
        value += (s[i] == 'T' ? 2 : 1);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    string lollipop(n, 'W');

    if (mode == 0) {
        char flavor = rnd.next(0, 1) ? 'T' : 'W';
        fill(lollipop.begin(), lollipop.end(), flavor);
    } else if (mode == 1) {
        char first = rnd.next(0, 1) ? 'T' : 'W';
        for (int i = 0; i < n; ++i) {
            lollipop[i] = (i % 2 == 0 ? first : (first == 'T' ? 'W' : 'T'));
        }
    } else if (mode == 2) {
        char flavor = rnd.next(0, 1) ? 'T' : 'W';
        for (int i = 0; i < n;) {
            int len = rnd.next(1, min(6, n - i));
            for (int j = 0; j < len; ++j) {
                lollipop[i + j] = flavor;
            }
            flavor = (flavor == 'T' ? 'W' : 'T');
            i += len;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            lollipop[i] = rnd.next(0, 99) < 65 ? 'T' : 'W';
        }
    } else if (mode == 4) {
        fill(lollipop.begin(), lollipop.end(), 'T');
        int wCount = rnd.next(1, min(n, 4));
        for (int i = 0; i < wCount; ++i) {
            int pos = rnd.next(0, n - 1);
            if (rnd.next(0, 99) < 70) {
                pos = rnd.next(0, 1) ? rnd.next(max(0, n - 4), n - 1)
                                     : rnd.next(0, min(3, n - 1));
            }
            lollipop[pos] = 'W';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            lollipop[i] = rnd.next(0, 99) < 80 ? 'W' : 'T';
        }
    }

    set<int> queries;
    int total = valueOf(lollipop, 0, n - 1);
    queries.insert(1);
    queries.insert(2);
    queries.insert(total);
    queries.insert(min(2000000, total + 1));
    queries.insert(2000000);

    int maxSampleCount = min(12, n * (n + 1) / 2);
    int sampleCount = rnd.next(1, maxSampleCount);
    for (int i = 0; i < sampleCount; ++i) {
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        queries.insert(valueOf(lollipop, l, r));
    }

    for (int attempts = 0; static_cast<int>(queries.size()) < 12 && attempts < 30; ++attempts) {
        int around = rnd.next(max(1, total - 5), min(2000000, total + 5));
        queries.insert(around);
    }
    while (static_cast<int>(queries.size()) < 12) {
        queries.insert(rnd.next(1, 2000000));
    }

    vector<int> shuffledQueries(queries.begin(), queries.end());
    shuffle(shuffledQueries.begin(), shuffledQueries.end());
    int m = rnd.next(1, static_cast<int>(shuffledQueries.size()));
    shuffledQueries.resize(m);

    println(n, m);
    println(lollipop);
    for (int query : shuffledQueries) {
        println(query);
    }

    return 0;
}

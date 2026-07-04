#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static string fromCounts(vector<int> counts) {
    string s;
    for (int c = 0; c < (int)counts.size(); ++c) {
        s.append(counts[c], char('a' + c));
    }
    shuffle(s.begin(), s.end());
    return s;
}

static string randomString(int len, int alphabet) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('a' + rnd.next(0, alphabet - 1));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 15);
    string s;

    if (mode == 0) {
        int alphabet = rnd.next(2, min(26, 2 * n));
        s = randomString(2 * n, alphabet);
    } else if (mode == 1) {
        vector<int> counts(26, 0);
        int dominant = rnd.next(0, 25);
        counts[dominant] = rnd.next(n, max(n, 2 * n - 1));
        int remaining = 2 * n - counts[dominant];
        while (remaining > 0) {
            int c = rnd.next(0, 25);
            if (c == dominant) continue;
            ++counts[c];
            --remaining;
        }
        s = fromCounts(counts);
    } else if (mode == 2) {
        vector<int> counts(26, 0);
        int a = rnd.next(0, 25);
        int b = rnd.next(0, 24);
        if (b >= a) ++b;
        counts[a] = rnd.next(1, 2 * n - 1);
        counts[b] = 2 * n - counts[a];
        s = fromCounts(counts);
    } else if (mode == 3) {
        vector<int> counts(26, 0);
        int alphabet = rnd.next(2, min(10, 2 * n));
        for (int i = 0; i < 2 * n; ++i) {
            ++counts[i % alphabet];
        }
        s = fromCounts(counts);
    } else if (mode == 4) {
        int alphabet = min(26, 2 * n);
        for (int i = 0; i < 2 * n; ++i) {
            s += char('a' + (i % alphabet));
        }
        shuffle(s.begin(), s.end());
    } else {
        char c = char('a' + rnd.next(0, 25));
        s.assign(2 * n, c);
    }

    println(s);
    return 0;
}

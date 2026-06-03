#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static string randomBinaryString(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('0' + rnd.next(0, 1)));
    }
    return s;
}

static string alternatingString(int n, char first) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back((i % 2 == 0) ? first : char('0' + '1' - first));
    }
    return s;
}

static string runLengthString(int n) {
    string s;
    s.reserve(n);
    char bit = char('0' + rnd.next(0, 1));
    while ((int)s.size() < n) {
        int remaining = n - (int)s.size();
        int run = rnd.next(1, min(remaining, rnd.next(1, 6)));
        s.append(run, bit);
        bit = char('0' + '1' - bit);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 60);
    string s;

    if (mode == 0) {
        s.assign(n, char('0' + rnd.next(0, 1)));
    } else if (mode == 1) {
        int zeros = rnd.next(0, n);
        if (rnd.next(0, 1) == 0) {
            s.assign(zeros, '0');
            s.append(n - zeros, '1');
        } else {
            s.assign(n - zeros, '1');
            s.append(zeros, '0');
        }
    } else if (mode == 2) {
        s = alternatingString(n, char('0' + rnd.next(0, 1)));
    } else if (mode == 3) {
        s.assign(n, char('0' + rnd.next(0, 1)));
        int flips = rnd.next(1, min(n, 8));
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < flips; ++i) {
            s[pos[i]] = char('0' + '1' - s[pos[i]]);
        }
    } else if (mode == 4) {
        s = runLengthString(n);
    } else {
        s = randomBinaryString(n);
    }

    println(s);
    return 0;
}

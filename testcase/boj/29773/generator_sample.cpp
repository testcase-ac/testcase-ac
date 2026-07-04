#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long fromDigits(const string& s) {
    long long value = 0;
    for (char c : s) {
        value = value * 10 + (c - '0');
    }
    return value;
}

string randomDigits(int len, bool allowLeadingZero = false) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        int lo = (i == 0 && !allowLeadingZero) ? 1 : 0;
        s.push_back(char('0' + rnd.next(lo, 9)));
    }
    return s;
}

long long with2023Subsequence() {
    int len = rnd.next(4, 18);
    vector<int> pos(len);
    for (int i = 0; i < len; ++i) pos[i] = i;
    shuffle(pos.begin(), pos.end());
    pos.resize(4);
    sort(pos.begin(), pos.end());

    string s = randomDigits(len);
    const string target = "2023";
    for (int i = 0; i < 4; ++i) s[pos[i]] = target[i];
    if (s[0] == '0') s[0] = char('1' + rnd.next(0, 8));

    long long value = fromDigits(s);
    if (value > 1000000000000000000LL) {
        value = rnd.next(900000000000000000LL, 1000000000000000000LL);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000000LL;
    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        n = rnd.next(1LL, 2022LL);
    } else if (mode == 1) {
        n = rnd.next(2010LL, 2040LL);
    } else if (mode == 2) {
        n = with2023Subsequence();
    } else if (mode == 3) {
        int len = rnd.next(4, 12);
        n = fromDigits(randomDigits(len));
    } else if (mode == 4) {
        vector<long long> anchors = {
            9999LL,
            20230LL,
            202300LL,
            1000000LL,
            123456789LL,
            999999999999999999LL,
            maxN,
        };
        long long base = rnd.any(anchors);
        long long delta = rnd.next(-1000LL, 1000LL);
        n = max(1LL, min(maxN, base + delta));
    } else {
        n = rnd.next(1LL, maxN);
    }

    println(n);
    return 0;
}

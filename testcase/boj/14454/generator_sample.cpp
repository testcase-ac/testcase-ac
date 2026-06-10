#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static const long long LIMIT = 1000000000000000000LL;

string makeString(int mode, int len) {
    string s;
    if (mode == 0) {
        char c = char('A' + rnd.next(26));
        s.assign(len, c);
    } else if (mode == 1) {
        for (int i = 0; i < len; ++i) s.push_back(char('A' + (i % 26)));
    } else if (mode == 2) {
        string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < len; ++i) s.push_back(alphabet[rnd.next(0, 3)]);
    } else {
        for (int i = 0; i < len; ++i) s.push_back(char('A' + rnd.next(26)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int lengthMode = rnd.next(5);
    int len;
    if (lengthMode == 0) len = 1;
    else if (lengthMode == 1) len = rnd.next(2, 5);
    else if (lengthMode == 2) len = rnd.next(6, 15);
    else if (lengthMode == 3) len = rnd.next(16, 29);
    else len = 30;

    string s = makeString(rnd.next(4), len);

    vector<long long> sizes;
    long long cur = len;
    sizes.push_back(cur);
    while (cur <= LIMIT / 2) {
        cur *= 2;
        sizes.push_back(cur);
    }

    int nMode = rnd.next(8);
    long long n;
    if (nMode == 0) {
        n = rnd.next(1, len);
    } else if (nMode == 1) {
        long long block = rnd.any(sizes);
        n = block;
    } else if (nMode == 2) {
        long long block = rnd.any(sizes);
        n = min(LIMIT, block + 1);
    } else if (nMode == 3) {
        long long block = rnd.any(sizes);
        long long lo = max(1LL, block / 2);
        n = rnd.next(lo, block);
    } else if (nMode == 4) {
        long long hi = min(1000LL, LIMIT);
        n = rnd.next(1LL, hi);
    } else if (nMode == 5) {
        n = LIMIT - rnd.next(0LL, 1000LL);
    } else if (nMode == 6) {
        long long block = rnd.any(sizes);
        long long span = min(1000000LL, block);
        long long offset = rnd.next(0LL, span - 1);
        n = block - offset;
    } else {
        n = rnd.next(1LL, LIMIT);
    }

    println(s, n);
    return 0;
}

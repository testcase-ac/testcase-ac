#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long randomT(int n) {
    int mode = rnd.next(7);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 30);
    if (mode == 2) return 1LL << rnd.next(1, 40);
    if (mode == 3) return (1LL << rnd.next(1, 40)) + rnd.next(0, n - 1);
    if (mode == 4) return rnd.next(1LL, 1000000000000000LL);
    if (mode == 5) return 1000000000000000LL - rnd.next(0, 1000);
    return rnd.next(1, 3) * 1LL * n + rnd.next(0, n - 1);
}

string randomState(int n) {
    string s(n, '0');
    int mode = rnd.next(8);

    if (mode == 0) {
        return s;
    }
    if (mode == 1) {
        fill(s.begin(), s.end(), '1');
        return s;
    }
    if (mode == 2) {
        s[rnd.next(n)] = '1';
        return s;
    }
    if (mode == 3) {
        int start = rnd.next(n);
        int len = rnd.next(1, n);
        for (int i = 0; i < len; ++i) s[(start + i) % n] = '1';
        return s;
    }
    if (mode == 4) {
        for (int i = 0; i < n; ++i) s[i] = char('0' + (i & 1));
        if (rnd.next(2)) reverse(s.begin(), s.end());
        return s;
    }
    if (mode == 5) {
        int period = rnd.next(2, min(n, 8));
        string pattern;
        for (int i = 0; i < period; ++i) pattern += char('0' + rnd.next(2));
        if (pattern.find('1') == string::npos) pattern[rnd.next(period)] = '1';
        for (int i = 0; i < n; ++i) s[i] = pattern[i % period];
        return s;
    }
    if (mode == 6) {
        int ones = rnd.next(1, min(n, 8));
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < ones; ++i) s[positions[i]] = '1';
        return s;
    }

    double density = rnd.next(0.15, 0.85);
    for (int i = 0; i < n; ++i) {
        if (rnd.next() < density) s[i] = '1';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(5);
    if (sizeMode == 0) n = 3;
    else if (sizeMode == 1) n = rnd.next(4, 10);
    else if (sizeMode == 2) n = rnd.next(11, 30);
    else if (sizeMode == 3) n = rnd.next(31, 80);
    else n = rnd.next(99950, 100000);

    println(n, randomT(n));
    println(randomState(n));
    return 0;
}

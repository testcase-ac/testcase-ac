#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long randomN(int mode) {
    const long long maxN = 1000000000000000000LL;

    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2LL, 20LL);
    if (mode == 2) return rnd.next(maxN - 1000LL, maxN);
    if (mode == 3) {
        vector<long long> candidates = {
            2LL, 3LL, 4LL, 5LL, 10LL, 100LL, 1000000007LL,
            1000000008LL, maxN / 2, maxN - 1, maxN};
        return rnd.any(candidates);
    }

    return rnd.next(1LL, maxN);
}

int randomM(int mode) {
    if (mode == 2) return rnd.next(40, 120);
    if (mode == 3) {
        vector<int> candidates = {1, 2, 3, 30, 60, 100, 200};
        return rnd.any(candidates);
    }

    return rnd.next(1, 40);
}

string randomBinaryString(int m, int pattern) {
    string x(m, '0');

    if (pattern == 0) return x;
    if (pattern == 1) return string(m, '1');
    if (pattern == 2) {
        for (int i = 0; i < m; ++i) x[i] = char('0' + (i % 2));
        if (rnd.next(2)) reverse(x.begin(), x.end());
        return x;
    }
    if (pattern == 3) {
        int ones = rnd.next(1, min(m, 5));
        vector<int> positions(m);
        for (int i = 0; i < m; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < ones; ++i) x[positions[i]] = '1';
        return x;
    }

    for (int i = 0; i < m; ++i) x[i] = char('0' + rnd.next(2));
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    long long n = randomN(mode);
    int m = randomM(mode);
    string x = randomBinaryString(m, rnd.next(5));

    println(n, m);
    println(x);

    return 0;
}

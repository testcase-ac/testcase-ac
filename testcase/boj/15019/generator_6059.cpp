#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose k up to 20, n up to min(15, 2^k)
    int k = rnd.next(1, 20);
    int maxn = min(15, 1 << min(k, 4)); // if k>=4, 1<<4=16 cap; else 2^k
    int n = rnd.next(1, maxn);

    vector<string> vs(n, string(k, '0'));
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        // include all-zeros and all-ones
        if (n >= 1) vs[0] = string(k, '0');
        if (n >= 2) vs[1] = string(k, '1');
        for (int i = 2; i < n; i++) {
            for (int j = 0; j < k; j++)
                vs[i][j] = char('0' + rnd.next(0, 1));
        }
    } else if (mode == 1) {
        // fixed ones count near k/2
        int mid = k / 2;
        int ones = mid + rnd.next(-1, 1);
        ones = max(0, min(k, ones));
        vector<int> pos(k);
        iota(pos.begin(), pos.end(), 0);
        for (int i = 0; i < n; i++) {
            shuffle(pos.begin(), pos.end());
            string s(k, '0');
            for (int t = 0; t < ones; t++)
                s[pos[t]] = '1';
            vs[i] = s;
        }
    } else if (mode == 2) {
        // Bernoulli per bit
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++)
                vs[i][j] = rnd.next() < p ? '1' : '0';
        }
    } else {
        // cluster around a base string
        string base(k, '0');
        for (int j = 0; j < k; j++)
            base[j] = char('0' + rnd.next(0, 1));
        double pFlip = rnd.next(0.0, 0.5);
        for (int i = 0; i < n; i++) {
            vs[i] = base;
            for (int j = 0; j < k; j++)
                if (rnd.next() < pFlip)
                    vs[i][j] = (vs[i][j] == '0' ? '1' : '0');
        }
    }

    // Introduce some duplicates randomly
    if (n > 2 && rnd.next(0, 1) == 1) {
        int dups = rnd.next(1, n / 2);
        for (int t = 0; t < dups; t++) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            vs[a] = vs[b];
        }
    }

    shuffle(vs.begin(), vs.end());
    // Output
    println(n, k);
    for (auto &s : vs) println(s);

    return 0;
}

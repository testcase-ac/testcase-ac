#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 2000000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 250);
    } else if (mode == 1) {
        n = rnd.next(maxN - 1000000, maxN);
    } else if (mode == 2) {
        n = rnd.next(1, maxN);
    } else {
        vector<int> g(1, 0);
        vector<long long> prefix(1, 0);
        for (int i = 1; i <= 200000 && prefix.back() < maxN; ++i) {
            int value = (i == 1) ? 1 : 1 + g[i - g[g[i - 1]]];
            g.push_back(value);
            prefix.push_back(prefix.back() + 1LL * i * value);
        }

        int idx = rnd.next(1, (int)prefix.size() - 1);
        long long base = (mode == 3) ? prefix[idx - 1] : prefix[idx];
        int delta = rnd.next(-3, 3);
        long long candidate = base + delta;
        if (candidate < 1) candidate = 1;
        if (candidate > maxN) candidate = maxN;
        n = (int)candidate;
    }

    println(n);
    return 0;
}

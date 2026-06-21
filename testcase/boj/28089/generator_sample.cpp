#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

long long randomK() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(1, 20);
    if (mode == 2) return 1LL << rnd.next(0, 20);
    if (mode == 3) return (1LL << rnd.next(0, 20)) - 1;
    if (mode == 4) return 1000000000000000000LL - rnd.next(0, 1000);
    return rnd.next(0LL, 1000000000000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, mode == 5 ? 200 : 60);
    long long k = randomK();
    set<int> chosen;

    if (mode == 0) {
        chosen.insert(rnd.next(0, n - 1));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) chosen.insert(i);
    } else if (mode == 2) {
        int parity = rnd.next(0, 1);
        for (int i = parity; i < n; i += 2) chosen.insert(i);
        if (chosen.empty()) chosen.insert(rnd.next(0, n - 1));
    } else if (mode == 3) {
        int blocks = rnd.next(1, min(4, n));
        for (int b = 0; b < blocks; ++b) {
            int start = rnd.next(0, n - 1);
            int len = rnd.next(1, min(8, n));
            for (int j = 0; j < len; ++j) chosen.insert((start + j) % n);
        }
    } else {
        int m = rnd.next(1, n);
        while ((int)chosen.size() < m) chosen.insert(rnd.next(0, n - 1));
    }

    vector<int> greeters(chosen.begin(), chosen.end());
    shuffle(greeters.begin(), greeters.end());

    println(n, (int)greeters.size(), k);
    for (int x : greeters) println(x);

    return 0;
}

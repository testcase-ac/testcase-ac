#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MIN_N = 1;
    const int MAX_N = 1000000;
    vector<int> interesting = {
        MIN_N, 2, 3, 4,
        1953, 1973, 2013, 2014, 2060,
        MAX_N - 2, MAX_N - 1, MAX_N
    };

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.any(interesting);
    } else if (mode == 1) {
        int base = rnd.next(0, MAX_N / 60) * 60 + 4;
        int delta = rnd.next(-2, 2);
        n = base + delta;
        n = max(MIN_N, min(MAX_N, n));
    } else if (mode == 2) {
        int residue = rnd.next(0, 59);
        int maxK = (MAX_N - 1 - residue) / 60;
        n = 1 + residue + 60 * rnd.next(0, maxK);
    } else if (mode == 3) {
        n = rnd.next(1, 3000);
    } else {
        n = rnd.next(MIN_N, MAX_N);
    }

    println(n);
    return 0;
}

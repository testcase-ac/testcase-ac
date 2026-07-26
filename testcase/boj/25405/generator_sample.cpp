#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int mode = rnd.next(0, 3);
    long long base = mode == 3 ? 1000000000LL - 20 : rnd.next(1, 30);
    vector<long long> levels(n);
    for (long long& level : levels)
        level = mode == 0 ? base : base + rnd.next(0, mode == 1 ? 2 : 20);

    int k = rnd.any(vector<int>{1, n, rnd.next(1, n)});
    int m = rnd.any(vector<int>{1, rnd.next(2, 30), 1000000000});
    println(n);
    println(levels);
    println(m, k);
}

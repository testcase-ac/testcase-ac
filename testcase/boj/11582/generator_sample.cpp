#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int exp = rnd.next(2, 8);
    int n = 1 << exp;
    int kExp = rnd.next(0, exp - 1);
    int k = 1 << kExp;
    int mode = rnd.next(0, 5);

    vector<long long> a(n);
    if (mode == 0) {
        for (long long& x : a) x = rnd.next(0, 30);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a[i] = i;
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = n - 1 - i;
    } else if (mode == 3) {
        long long base = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) a[i] = base + rnd.next(0, 3);
    } else if (mode == 4) {
        for (long long& x : a) {
            int pick = rnd.next(0, 4);
            if (pick == 0) x = 0;
            else if (pick == 1) x = 1000000000LL;
            else x = rnd.next(0, 1000000000);
        }
    } else {
        int block = n / k;
        for (int i = 0; i < n; ++i) {
            int offset = i % block;
            a[i] = offset + rnd.next(0, 2) * block;
        }
        for (int start = 0; start < n; start += block) {
            if (rnd.next(0, 1)) {
                reverse(a.begin() + start, a.begin() + start + block);
            }
        }
    }

    println(n);
    println(a);
    println(k);
    return 0;
}

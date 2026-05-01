#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(6, 12);
    vector<int> Xs;
    Xs.reserve(T);
    for (int i = 0; i < T; i++) {
        int type = rnd.next(1, 6);
        int X = 1;
        if (type == 1) {
            // Fully random
            X = rnd.next(1, 1000000000);
        } else if (type == 2) {
            // Near a power of two
            int k = rnd.next(1, 29);
            int base = 1 << k;
            int d = rnd.next(0, 5);
            if (rnd.next(0, 1) == 0) d = -d;
            X = base + d;
            if (X < 1) X = 1;
        } else if (type == 3) {
            // Near 2^k - 1 (all ones)
            int k = rnd.next(1, 29);
            int base = (1 << k) - 1;
            int d = rnd.next(0, 5);
            if (rnd.next(0, 1) == 0) d = -d;
            X = base + d;
            if (X < 1) X = 1;
        } else if (type == 4) {
            // Around a binary palindrome
            int L = rnd.next(2, 30);
            vector<int> b(L);
            b[0] = 1;
            int half = (L + 1) / 2;
            for (int j = 1; j < half; j++)
                b[j] = rnd.next(0, 1);
            for (int j = 0; j < half; j++)
                b[L - 1 - j] = b[j];
            long long val = 0;
            for (int j = 0; j < L; j++)
                val = (val << 1) | b[j];
            int base = int(val);
            int d = rnd.next(0, 10);
            if (rnd.next(0, 1) == 0) d = -d;
            X = base + d;
            if (X < 1) X = 1;
            if (X > 1000000000) X = 1000000000;
        } else if (type == 5) {
            // Small X
            X = rnd.next(1, 20);
        } else {
            // Large X
            X = rnd.next(1000000000 - 1000, 1000000000);
        }
        Xs.push_back(X);
    }
    shuffle(Xs.begin(), Xs.end());
    println(T);
    for (int x : Xs) println(x);
    return 0;
}

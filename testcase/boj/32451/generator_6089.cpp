#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sample n from 1..12, biased towards small values
    int n = rnd.wnext(12, -1) + 1;
    vector<int> a(n), b(n);
    // 10% trivial identical case
    if (rnd.next(0, 9) == 0) {
        for (int i = 0; i < n; i++) a[i] = i + 1;
        shuffle(a.begin(), a.end());
        b = a;
    }
    // 10% sorted vs reversed case (may be solvable or not depending on parity)
    else if (rnd.next(0, 9) == 1 && n > 1) {
        for (int i = 0; i < n; i++) {
            a[i] = i + 1;
            b[i] = n - i;
        }
    }
    // General random cases with control over solvability
    else {
        // ~70% solvable, rest unsolvable (when n>1)
        bool solvable = rnd.next(0, 9) < 7;
        bool needSol = solvable || n < 2;
        // Helper to generate a permutation of 1..n with specified parity
        auto genWithParity = [&](vector<int>& v, int desiredParity) {
            for (int i = 0; i < n; i++) v[i] = i + 1;
            shuffle(v.begin(), v.end());
            if (n > 1) {
                int p = 0;
                for (int i = 0; i < n; i++)
                    for (int j = i + 1; j < n; j++)
                        if (v[i] > v[j]) p ^= 1;
                if (p != desiredParity) swap(v[0], v[1]);
            }
        };
        if (needSol) {
            int targetP = rnd.next(0, 1);
            genWithParity(a, targetP);
            genWithParity(b, targetP);
        } else {
            // force opposite parity to make it impossible
            int pa = rnd.next(0, 1);
            int pb = pa ^ 1;
            genWithParity(a, pa);
            genWithParity(b, pb);
        }
    }
    // Output
    println(n);
    println(a);
    println(b);
    return 0;
}

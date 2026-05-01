#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sample pattern length m: small enough to verify manually
    int m = rnd.next(1, 10);

    // Generate pattern P with different structures
    string P;
    int pmode = rnd.next(0, 2);
    if (pmode == 0) {
        // Completely random pattern
        P.resize(m);
        for (int i = 0; i < m; i++)
            P[i] = char(rnd.next('a', 'z'));
    } else if (pmode == 1) {
        // Uniform character pattern
        char c = rnd.any(string("abcdefghijklmnopqrstuvwxyz"));
        P = string(m, c);
    } else {
        // Repeated substring pattern to create overlaps
        int sublen = rnd.next(1, m);
        string sub(sublen, ' ');
        for (int i = 0; i < sublen; i++)
            sub[i] = char(rnd.next('a', 'z'));
        P = "";
        while ((int)P.size() < m) {
            P += sub;
        }
        P.resize(m);
    }

    // Sample target length n: small to moderate
    int n = rnd.next(1, 30);

    // Generate target T with different compositions
    string T;
    int tmode = rnd.next(0, 2);
    if (tmode == 0) {
        // Completely random target
        T.resize(n);
        for (int i = 0; i < n; i++)
            T[i] = char(rnd.next('a', 'z'));
    } else if (tmode == 1) {
        // Repeats of P plus maybe a tail
        int k = n / m;
        int rem = n % m;
        T = "";
        for (int i = 0; i < k; i++)
            T += P;
        if (rem > 0) {
            if (rnd.next(0, 1) == 0) {
                // take prefix of P
                T += P.substr(0, rem);
            } else {
                // random tail
                for (int i = 0; i < rem; i++)
                    T += char(rnd.next('a', 'z'));
            }
        }
    } else {
        // Mix of P and random chars
        T = "";
        while ((int)T.size() < n) {
            if (rnd.next(0, 1) == 0 && (int)T.size() + m <= n) {
                T += P;
            } else {
                T += char(rnd.next('a', 'z'));
            }
        }
        T.resize(n);
    }

    // Output the test case
    println(m, n);
    println(P);
    println(T);

    return 0;
}

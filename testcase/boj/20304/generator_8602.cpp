#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, M;
    vector<int> p;

    int type = rnd.next(0, 7);

    switch (type) {
        case 0: {
            // Trivial smallest case
            N = 0;
            M = 1;
            p.clear();
            p.push_back(0);
            break;
        }
        case 1: {
            // Small N, sometimes use all numbers
            N = rnd.next(1, 15);
            bool useAll = (rnd.next(0, 1) == 0);

            vector<int> all;
            for (int i = 0; i <= N; ++i) all.push_back(i);
            shuffle(all.begin(), all.end());

            if (useAll) {
                p = all;
                M = N + 1;
            } else {
                M = rnd.next(1, min(10, N + 1));
                all.resize(M);
                p = all;
            }
            break;
        }
        case 2: {
            // Moderate N, random or distinct attempts
            N = rnd.next(10, 200);
            M = rnd.next(1, min(20, N + 1));

            if (rnd.next(0, 1) == 0) {
                // Distinct attempts
                vector<int> all;
                for (int i = 0; i <= N; ++i) all.push_back(i);
                shuffle(all.begin(), all.end());
                all.resize(M);
                p = all;
            } else {
                // Possibly with duplicates
                p.resize(M);
                for (int i = 0; i < M; ++i)
                    p[i] = rnd.next(0, N);
            }
            break;
        }
        case 3: {
            // N = 2^k - 1, full bit space of some length
            int k = rnd.next(3, 19); // ensures (1<<k)-1 <= 1,000,000
            N = (1 << k) - 1;
            M = rnd.next(1, min(25, N + 1));
            p.resize(M);
            for (int i = 0; i < M; ++i)
                p[i] = rnd.next(0, N);
            break;
        }
        case 4: {
            // N just below a power-of-two-full range
            int k = rnd.next(5, 19);
            int full = (1 << k) - 1;
            int deltaMax = (1 << (k - 1));
            int delta = rnd.next(1, deltaMax);
            N = full - delta; // not of form 2^k - 1
            if (N < 0) N = 0; // safety, though shouldn't happen
            M = rnd.next(1, min(25, N + 1));
            p.resize(M);
            for (int i = 0; i < M; ++i)
                p[i] = rnd.next(0, N);
            break;
        }
        case 5: {
            // Always include 0 and N, plus others
            N = rnd.next(1, 1000);
            M = rnd.next(2, min(20, N + 1));
            p.clear();
            p.push_back(0);
            p.push_back(N);
            while ((int)p.size() < M) {
                int v;
                int mode = rnd.next(0, 4);
                if (mode == 0) v = 0;
                else if (mode == 1) v = N;
                else v = rnd.next(0, N);
                p.push_back(v);
            }
            shuffle(p.begin(), p.end());
            break;
        }
        case 6: {
            // Clustered around a center using bit flips
            N = rnd.next(20, 1000);
            M = rnd.next(2, min(20, N + 1));
            int center = rnd.next(0, N);

            int maxv = max(N, center);
            int bitlen = 0;
            while ((1 << bitlen) <= maxv) bitlen++;
            if (bitlen == 0) bitlen = 1;

            p.clear();
            p.push_back(center);
            for (int b = 0; b < bitlen && (int)p.size() < M; ++b) {
                int v = center ^ (1 << b);
                if (0 <= v && v <= N) p.push_back(v);
            }
            while ((int)p.size() < M) {
                int v;
                if (rnd.next(0, 1) == 0) {
                    int b1 = rnd.next(0, bitlen - 1);
                    v = center ^ (1 << b1);
                    if (!(0 <= v && v <= N)) v = rnd.next(0, N);
                } else {
                    v = rnd.next(0, N);
                }
                p.push_back(v);
            }
            shuffle(p.begin(), p.end());
            break;
        }
        case 7: {
            // Large N near upper bound, small M
            N = rnd.next(100000, 1000000);
            M = rnd.next(1, 20);
            p.clear();
            if (M == 1) {
                int t = rnd.next(0, 2);
                if (t == 0) p.push_back(0);
                else if (t == 1) p.push_back(N);
                else p.push_back(rnd.next(0, N));
            } else {
                p.push_back(0);
                p.push_back(N);
                while ((int)p.size() < M)
                    p.push_back(rnd.next(0, N));
                shuffle(p.begin(), p.end());
            }
            break;
        }
    }

    println(N);
    println((int)p.size());
    println(p);

    return 0;
}

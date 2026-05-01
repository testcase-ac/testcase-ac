#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate N as a multiple of 3 between 3 and 48
    int N = 3 * rnd.next(1, 16);
    int type = rnd.next(0, 3);
    vector<int> P(N), S(N);

    if (type == 0) {
        // Identity shuffle, random P => likely impossible (-1)
        for (int i = 0; i < N; i++) {
            S[i] = i;
            P[i] = rnd.next(0, 2);
        }
    } else if (type == 1) {
        // Identity shuffle, P aligned => answer 0
        for (int i = 0; i < N; i++) {
            S[i] = i;
            P[i] = i % 3;
        }
    } else if (type == 2) {
        // Cyclic shift shuffle, guaranteed solution at k>0
        int shift = rnd.next(1, N-1);
        for (int i = 0; i < N; i++) {
            S[i] = (i + shift) % N;
        }
        int k = rnd.next(1, 10);
        vector<int> cur(N);
        iota(cur.begin(), cur.end(), 0);
        for (int t = 0; t < k; t++) {
            for (int i = 0; i < N; i++) {
                cur[i] = S[cur[i]];
            }
        }
        for (int i = 0; i < N; i++) {
            P[i] = cur[i] % 3;
        }
    } else {
        // Random shuffle, guaranteed solution at k>0
        vector<int> tmp(N);
        iota(tmp.begin(), tmp.end(), 0);
        shuffle(tmp.begin(), tmp.end());
        for (int i = 0; i < N; i++) {
            S[i] = tmp[i];
        }
        int k = rnd.next(1, 10);
        vector<int> cur(N);
        iota(cur.begin(), cur.end(), 0);
        for (int t = 0; t < k; t++) {
            for (int i = 0; i < N; i++) {
                cur[i] = S[cur[i]];
            }
        }
        for (int i = 0; i < N; i++) {
            P[i] = cur[i] % 3;
        }
    }

    // Output
    println(N);
    println(P);
    println(S);
    return 0;
}

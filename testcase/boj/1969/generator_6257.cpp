#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: small, medium, large
    int N;
    double pN = rnd.next();
    if (pN < 0.33) {
        N = rnd.next(1, 3);
    } else if (pN < 0.66) {
        N = rnd.next(4, 10);
    } else {
        N = rnd.next(11, 20);
    }
    // Hyper-parameter for M: small, medium, large (cap at 30)
    int M;
    double pM = rnd.next();
    if (pM < 0.33) {
        M = rnd.next(1, 5);
    } else if (pM < 0.66) {
        M = rnd.next(6, 20);
    } else {
        M = rnd.next(21, 30);
    }
    // Generate random DNA strings
    vector<string> dna(N, string(M, 'A'));
    const string bases = "ACGT";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dna[i][j] = rnd.any(bases);
        }
    }
    // Enforce some tie situations per column
    for (int j = 0; j < M; j++) {
        if (N >= 2 && rnd.next() < 0.3) {
            // pick two distinct bases
            char a = rnd.any(bases), b = rnd.any(bases);
            while (b == a) b = rnd.any(bases);
            if (a > b) swap(a, b);
            vector<int> idx(N);
            for (int i = 0; i < N; i++) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            int half = N / 2;
            for (int t = 0; t < half; t++) {
                dna[idx[t]][j] = a;
            }
            for (int t = half; t < 2*half; t++) {
                dna[idx[t]][j] = b;
            }
            // if odd remainder, leave original
        }
    }
    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(dna[i]);
    }
    return 0;
}

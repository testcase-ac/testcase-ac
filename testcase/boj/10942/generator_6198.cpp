#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sequence length
    int N = rnd.next(1, 20);
    vector<int> a(N);

    // Choose sequence pattern for variability
    int seqType = rnd.next(1, 4);
    if (seqType == 1) {
        // Fully random
        int K = rnd.next(1, 1000);
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, K);
    } else if (seqType == 2) {
        // A palindrome
        int K = rnd.next(1, 1000);
        for (int i = 0; i <= (N-1)/2; i++) {
            int v = rnd.next(1, K);
            a[i] = v;
            a[N-1-i] = v;
        }
    } else if (seqType == 3) {
        // Repeating small pattern
        int Kp = rnd.next(1, 100);
        int Lp = rnd.next(1, min(N, 5));
        vector<int> pat(Lp);
        for (int i = 0; i < Lp; i++)
            pat[i] = rnd.next(1, Kp);
        for (int i = 0; i < N; i++)
            a[i] = pat[i % Lp];
    } else {
        // Alternating two values
        int x = rnd.next(1, 1000);
        int y = rnd.next(1, 1000);
        for (int i = 0; i < N; i++)
            a[i] = (i % 2 ? y : x);
    }

    // Precompute palindromic intervals
    vector<vector<char>> isPal(N, vector<char>(N, 0));
    for (int i = 0; i < N; i++)
        isPal[i][i] = 1;
    for (int i = 0; i+1 < N; i++)
        isPal[i][i+1] = (a[i] == a[i+1]);
    for (int len = 3; len <= N; len++) {
        for (int i = 0; i + len <= N; i++) {
            int j = i + len - 1;
            isPal[i][j] = isPal[i+1][j-1] && (a[i] == a[j]);
        }
    }

    vector<pair<int,int>> palP, nonPalP;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (isPal[i][j]) palP.emplace_back(i, j);
            else nonPalP.emplace_back(i, j);
        }
    }

    // Number of queries
    int M = rnd.next(1, min(50, N*N));
    // Output
    println(N);
    println(a);
    println(M);

    // Generate queries with mixed types
    for (int i = 0; i < M; i++) {
        int t = rnd.next(1, 100);
        int s = 0, e = 0;
        if (t <= 20) {
            // Single element
            s = e = rnd.next(0, N-1);
        } else if (t <= 40) {
            // Entire array
            s = 0; e = N-1;
        } else if (t <= 70 && !palP.empty()) {
            // Ensure palindrome
            auto pr = rnd.any(palP);
            s = pr.first; e = pr.second;
        } else {
            // Ensure non-palindrome if possible
            if (nonPalP.empty()) {
                auto pr = rnd.any(palP);
                s = pr.first; e = pr.second;
            } else {
                auto pr = rnd.any(nonPalP);
                s = pr.first; e = pr.second;
            }
        }
        // Output 1-based
        println(s+1, e+1);
    }

    return 0;
}

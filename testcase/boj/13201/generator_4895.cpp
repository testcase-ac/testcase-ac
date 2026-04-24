#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    // Pool of airport codes including ICN
    vector<string> pool = {
        "GMP","ICN","CJU","PUS","SEL","FUK","PEK","NRT","HND",
        "SFO","LAX","JFK","AMS","CDG","DFW","DXB","LHR","SYD","HKG","KUL"
    };
    // Remove ICN from pool so we don't duplicate
    pool.erase(find(pool.begin(), pool.end(), "ICN"));
    shuffle(pool.begin(), pool.end());
    for (int tc = 0; tc < T; tc++) {
        // Number of airports
        int N = rnd.next(2, 6);
        // Generate K with bias: sometimes small, sometimes large
        vector<int> wv = {-2, -1, 0, 1, 2};
        int wt = rnd.any(wv);
        int K = rnd.wnext(10, wt) + 1;  // 1..10 biased
        // Choose airport codes: ICN at index 0
        vector<string> codes;
        codes.push_back("ICN");
        for (int i = 1; i < N; i++) {
            codes.push_back(pool[i - 1]);
        }
        shuffle(codes.begin() + 1, codes.end());
        // Output N, K and codes
        println(N, K);
        for (auto &s : codes) println(s);
        // Build flight count matrix S
        int den100 = rnd.next(30, 100);  // density percentage
        int maxF = rnd.next(1, 10);
        vector<vector<int>> S(N, vector<int>(N, 0));
        for (int i = 0; i < N; i++) {
            int rowSum = 0;
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                if (rnd.next(1, 100) <= den100) {
                    S[i][j] = rnd.next(1, maxF);
                    rowSum += S[i][j];
                }
            }
            // Ensure at least one outgoing flight
            if (rowSum == 0) {
                int j = rnd.next(0, N - 2);
                if (j >= i) j++;
                S[i][j] = rnd.next(1, maxF);
            }
        }
        // Print matrix
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d", S[i][j]);
                if (j + 1 < N) printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}

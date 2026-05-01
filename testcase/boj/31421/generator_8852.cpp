#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(1, 100);
    int N;
    string S;

    if (mode <= 25) {
        // Special small / edge cases
        vector<string> special = {
            "W", "B",
            "WW", "WB", "BW", "BB",
            "WWW", "BBB", "WBW", "BWB", "WBB", "BWW",
            "WWWW", "BBBB", "WBBB", "BWWW", "WBWB", "BWBW"
        };
        S = rnd.any(special);
        N = (int)S.size();
    } else if (mode <= 60) {
        // Reachable patterns via random valid operations from all 'W'
        // N between 2 and 40
        if (rnd.next(0, 1) == 0)
            N = rnd.next(2, 10);
        else
            N = rnd.next(10, 40);

        vector<char> a(N, 'W');
        int K = rnd.next(0, N); // at most N operations

        for (int step = 0; step < K; ++step) {
            vector<int> cand;
            for (int x = 1; x <= N - 1; ++x) {
                if (a[x - 1] == a[x])
                    cand.push_back(x);
            }
            if (cand.empty())
                break;
            int x = rnd.any(cand); // 1-based index

            if (a[x - 1] == 'W') {
                // flip [1..x] -> [0..x-1]
                for (int i = 0; i < x; ++i)
                    a[i] = (a[i] == 'W' ? 'B' : 'W');
            } else {
                // flip [x+1..N] -> [x..N-1]
                for (int i = x; i < N; ++i)
                    a[i] = (a[i] == 'W' ? 'B' : 'W');
            }
        }

        S.assign(a.begin(), a.end());
    } else {
        // Random patterns, possibly unreachable
        // N between 1 and 80, biased towards small
        int choice = rnd.next(0, 4);
        if (choice == 0)
            N = rnd.next(1, 5);
        else if (choice == 1)
            N = rnd.next(3, 10);
        else if (choice == 2)
            N = rnd.next(5, 20);
        else
            N = rnd.next(10, 80);

        int patternType = rnd.next(0, 4);
        S.assign(N, 'W');

        if (patternType == 0) {
            // Fully random
            for (int i = 0; i < N; ++i)
                S[i] = rnd.next(0, 1) ? 'W' : 'B';
        } else if (patternType == 1) {
            // All same
            char c = rnd.next(0, 1) ? 'W' : 'B';
            for (int i = 0; i < N; ++i) S[i] = c;
        } else if (patternType == 2) {
            // Alternating
            char start = rnd.next(0, 1) ? 'W' : 'B';
            for (int i = 0; i < N; ++i) {
                if (i % 2 == 0) S[i] = start;
                else S[i] = (start == 'W' ? 'B' : 'W');
            }
        } else if (patternType == 3) {
            // Mostly W with few Bs
            for (int i = 0; i < N; ++i) S[i] = 'W';
            int k = rnd.next(1, max(1, N / 3));
            for (int t = 0; t < k; ++t) {
                int pos = rnd.next(0, N - 1);
                S[pos] = 'B';
            }
        } else {
            // Mostly B with few Ws
            for (int i = 0; i < N; ++i) S[i] = 'B';
            int k = rnd.next(1, max(1, N / 3));
            for (int t = 0; t < k; ++t) {
                int pos = rnd.next(0, N - 1);
                S[pos] = 'W';
            }
        }
    }

    println(N);
    println(S);

    return 0;
}

#include "testlib.h"
using namespace std;

long long genUnique(set<long long>& used, long long lo, long long hi) {
    while (true) {
        long long x = rnd.next(lo, hi);
        if (!used.count(x)) {
            used.insert(x);
            return x;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 5); // 0..5 => 6 types
    int N, M;
    vector<vector<long long>> a;

    if (type == 0) {
        // Example 1 from statement
        N = 3; M = 4;
        a = {
            {12, 16, 67, 43},
            {7, 17, 68, 48},
            {14, 15, 77, 54}
        };
    } else if (type == 1) {
        // Example 2 from statement
        N = 4; M = 3;
        a = {
            {10, 20, 30},
            {40, 50, 60},
            {70, 80, 90},
            {100, 110, 120}
        };
    } else if (type == 2) {
        // Random small matrix, all distinct, moderate values
        do {
            N = rnd.next(2, 7);
            M = rnd.next(2, 7);
        } while (N * M > 30);

        a.assign(N, vector<long long>(M));
        set<long long> used;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                a[i][j] = genUnique(used, 0, 200);
            }
        }
    } else if (type == 3) {
        // Clustered values: one "good" column with tight range, others far away
        do {
            N = rnd.next(3, 6);
            M = rnd.next(3, 6);
        } while (N * M > 30);

        a.assign(N, vector<long long>(M));
        int C = rnd.next(50, 100);
        int j0 = rnd.next(0, M - 1);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (j == j0) {
                    // Tight cluster: optimal solution should pick this column
                    a[i][j] = C + i; // differences up to N-1
                } else {
                    // Far values
                    a[i][j] = C + 50 + 13 * i + 7 * j;
                }
            }
        }
    } else if (type == 4) {
        // Degenerate shapes: N=1 or M=1
        bool oneClass = (rnd.next(0, 1) == 0);
        set<long long> used;
        if (oneClass) {
            N = 1;
            M = rnd.next(1, 7);
            a.assign(N, vector<long long>(M));
            for (int j = 0; j < M; ++j) {
                a[0][j] = genUnique(used, 0, 200);
            }
        } else {
            M = 1;
            N = rnd.next(1, 7);
            a.assign(N, vector<long long>(M));
            for (int i = 0; i < N; ++i) {
                a[i][0] = genUnique(used, 0, 200);
            }
        }
    } else { // type == 5
        // Extreme range: some very small, some near 1e9
        const long long B = 1000000000LL;
        do {
            N = rnd.next(2, 5);
            M = rnd.next(2, 5);
        } while (N * M > 20);

        a.assign(N, vector<long long>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int idx = i * M + j;
                if (idx % 2 == 0)
                    a[i][j] = idx;          // small
                else
                    a[i][j] = B - idx;      // large
            }
        }
    }

    println(N, M);
    for (int i = 0; i < N; ++i)
        println(a[i]);

    return 0;
}

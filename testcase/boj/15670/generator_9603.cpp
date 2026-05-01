#include "testlib.h"
using namespace std;

int generateQueries(int N, vector<pair<int,int>>& qs) {
    qs.clear();
    int maxM = min(25, N * (N + 1) / 2);
    int M = rnd.next(1, maxM);
    int type = rnd.next(0, 2); // 0,1,2

    if (type == 0) {
        // Mix of special and random queries
        qs.push_back(make_pair(1, N)); // whole segment
        qs.push_back(make_pair(1, 1)); // first element
        if (N > 1) {
            qs.push_back(make_pair(N, N)); // last element
            int pos = rnd.next(1, N - 1);
            qs.push_back(make_pair(pos, pos + 1)); // adjacent pair
        }
        if (N >= 3) {
            int mid = (N + 1) / 2;
            qs.push_back(make_pair(mid, mid)); // middle element
        }
        while ((int)qs.size() < M) {
            int l = rnd.next(1, N);
            int r = rnd.next(1, N);
            if (l > r) swap(l, r);
            qs.push_back(make_pair(l, r));
        }
    } else if (type == 1) {
        // Many small segments of various lengths
        for (int len = 1; len <= min(4, N) && (int)qs.size() < M; ++len) {
            for (int start = 1; start + len - 1 <= N && (int)qs.size() < M; ++start) {
                qs.push_back(make_pair(start, start + len - 1));
            }
        }
        while ((int)qs.size() < M) {
            int l = rnd.next(1, N);
            int r = rnd.next(1, N);
            if (l > r) swap(l, r);
            qs.push_back(make_pair(l, r));
        }
    } else {
        // Segments touching boundaries, then random
        for (int i = 1; i <= N && (int)qs.size() < M; ++i) {
            qs.push_back(make_pair(1, i));
        }
        for (int i = 1; i <= N && (int)qs.size() < M; ++i) {
            qs.push_back(make_pair(i, N));
        }
        while ((int)qs.size() < M) {
            int l = rnd.next(1, N);
            int r = rnd.next(1, N);
            if (l > r) swap(l, r);
            qs.push_back(make_pair(l, r));
        }
    }
    return M;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 7);

    int N = 0, M = 0;
    vector<int> a;
    vector<pair<int,int>> queries;

    switch (scenario) {
        case 0: {
            // Special scenario to catch "cumulative reversal" bug
            N = 5;
            a.resize(N);
            for (int i = 0; i < N; ++i) a[i] = i + 1; // 1 2 3 4 5

            // Carefully chosen queries: treating reversals cumulatively gives wrong answers
            M = 5;
            queries.clear();
            queries.push_back(make_pair(2, 4));
            queries.push_back(make_pair(2, 5));
            queries.push_back(make_pair(1, 5));
            queries.push_back(make_pair(1, 1));
            queries.push_back(make_pair(3, 3));
            break;
        }
        case 1: {
            // N = 1 edge case, multiple days
            N = 1;
            a.resize(N);
            a[0] = rnd.next(1, 1000000000);
            M = rnd.next(1, 5);
            queries.clear();
            for (int i = 0; i < M; ++i) {
                queries.push_back(make_pair(1, 1));
            }
            break;
        }
        case 2: {
            // Strictly increasing
            N = rnd.next(2, 12);
            a.resize(N);
            for (int i = 0; i < N; ++i) a[i] = i + 1; // 1..N
            M = generateQueries(N, queries);
            break;
        }
        case 3: {
            // Strictly decreasing
            N = rnd.next(2, 12);
            a.resize(N);
            for (int i = 0; i < N; ++i) a[i] = N - i; // N..1
            M = generateQueries(N, queries);
            break;
        }
        case 4: {
            // Random permutation
            N = rnd.next(5, 15);
            a.resize(N);
            for (int i = 0; i < N; ++i) a[i] = i + 1;
            shuffle(a.begin(), a.end());
            M = generateQueries(N, queries);
            break;
        }
        case 5: {
            // Bitonic: increasing then decreasing tail
            N = rnd.next(5, 15);
            a.resize(N);
            for (int i = 0; i < N; ++i) a[i] = i + 1;
            int p = rnd.next(2, N - 1); // pivot in (1, N)
            // Reverse suffix [p..N-1] (0-based)
            int l = p, r = N - 1;
            while (l < r) {
                swap(a[l], a[r]);
                ++l; --r;
            }
            M = generateQueries(N, queries);
            break;
        }
        case 6: {
            // Zigzag high-low pattern
            N = rnd.next(4, 14);
            vector<int> smalls, bigs;
            int half = (N + 1) / 2;
            for (int i = 1; i <= half; ++i) smalls.push_back(i);
            for (int i = N; i > half; --i) bigs.push_back(i);
            a.clear();
            for (int k = 0; k < N; ++k) {
                if (k % 2 == 0) {
                    a.push_back(smalls[k / 2]);
                } else {
                    a.push_back(bigs[k / 2]);
                }
            }
            M = generateQueries(N, queries);
            break;
        }
        case 7: {
            // Random permutation with spaced-out values
            N = rnd.next(5, 15);
            vector<int> perm(N);
            for (int i = 0; i < N; ++i) perm[i] = i + 1;
            shuffle(perm.begin(), perm.end());
            a.resize(N);
            // Map to distinct spaced values
            for (int i = 0; i < N; ++i) {
                a[i] = perm[i] * 1000 + 7;
            }
            M = generateQueries(N, queries);
            break;
        }
    }

    println(N, M);
    println(a);
    for (int i = 0; i < M; ++i) {
        println(queries[i].first, queries[i].second);
    }

    return 0;
}

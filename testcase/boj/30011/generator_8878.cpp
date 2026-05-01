#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(1, 8);
    int N;
    vector<int> A;

    switch (scenario) {
        case 1: {
            // Single polygon, various sizes
            N = 1;
            int type = rnd.next(1, 4);
            int v;
            if (type == 1) v = 3;
            else if (type == 2) v = 4;
            else if (type == 3) v = rnd.next(5, 10);
            else v = rnd.next(50, 100);
            A.push_back(v);
            break;
        }
        case 2: {
            // Long chain with equal sizes
            N = rnd.next(2, 20);
            vector<int> cand = {3, 4, 5, 6, 7, 8, 9, 10, 100};
            int v = rnd.any(cand);
            A.assign(N, v);
            break;
        }
        case 3: {
            // Strictly decreasing by 1
            N = rnd.next(2, 10);
            int baseLow = N + 2; // ensure last >= 3
            if (baseLow < 4) baseLow = 4;
            int baseHigh = min(100, N + 20);
            if (baseHigh < baseLow) baseHigh = baseLow;
            int base = rnd.next(baseLow, baseHigh);
            for (int i = 0; i < N; ++i)
                A.push_back(base - i);
            break;
        }
        case 4: {
            // Mixed plateaus and small drops
            N = rnd.next(5, 25);
            int cur = rnd.next(6, 100);
            A.push_back(cur);
            for (int i = 2; i <= N; ++i) {
                int maxDrop = cur - 3;
                int hi = maxDrop > 2 ? 2 : maxDrop;
                if (hi < 0) hi = 0;
                int delta = rnd.next(0, hi);
                cur -= delta;
                A.push_back(cur);
            }
            break;
        }
        case 5: {
            // Some larger polygons, then many triangles
            N = rnd.next(3, 30);
            int prefixLen = rnd.next(1, min(5, N));
            int cur = rnd.next(5, 100);
            for (int i = 1; i <= prefixLen; ++i) {
                A.push_back(cur);
                if (i < prefixLen) {
                    int maxDrop = cur - 4; // keep >= 4 within prefix (except possibly last)
                    if (maxDrop < 0) maxDrop = 0;
                    int hi = min(3, maxDrop);
                    int delta = rnd.next(0, hi);
                    cur -= delta;
                }
            }
            for (int i = prefixLen + 1; i <= N; ++i)
                A.push_back(3);
            break;
        }
        case 6: {
            // Predefined interesting patterns with big drops
            vector<vector<int>> patterns = {
                {4},
                {4, 4, 3},
                {4, 3},
                {5, 5, 5, 3},
                {6, 6, 4, 4, 3},
                {10, 10, 9, 3, 3, 3},
                {12, 12, 6, 6, 3},
                {7, 7, 7, 7, 3, 3},
                {100, 100, 3},
                {100, 50, 50, 3, 3},
                {6, 5, 4, 3, 3}
            };
            A = rnd.any(patterns);
            N = (int)A.size();
            break;
        }
        case 7: {
            // Medium N, many 3s/4s with gentle decreases
            N = rnd.next(20, 60);
            int cur = rnd.next(4, 10);
            A.push_back(cur);
            for (int i = 2; i <= N; ++i) {
                int newVal;
                if (rnd.next(0, 99) < 70) {
                    int hi = min(cur, 5);
                    if (hi < 3) hi = 3;
                    newVal = rnd.next(3, hi);
                } else {
                    newVal = rnd.next(3, cur);
                }
                cur = newVal;
                A.push_back(cur);
            }
            break;
        }
        case 8: {
            // Random multiset, then sorted non-increasing
            N = rnd.next(2, 15);
            A.resize(N);
            for (int i = 0; i < N; ++i)
                A[i] = rnd.next(3, 100);
            sort(A.begin(), A.end(), greater<int>());
            break;
        }
    }

    // Final safety: ensure non-increasing and >=3
    for (int i = 0; i < (int)A.size(); ++i) {
        if (A[i] < 3) A[i] = 3;
        if (i > 0 && A[i] > A[i - 1]) A[i] = A[i - 1];
    }

    N = (int)A.size();
    println(N);
    println(A);

    return 0;
}

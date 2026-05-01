#include "testlib.h"
using namespace std;

int computeL(int K, const vector<int>& s) {
    int L = (int)1e9;
    for (int x : s) {
        L = min(L, K / x);
    }
    return L;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, D, K;
    vector<int> s;

    int type = rnd.next(0, 5);

    if (type == 0) {
        // General small/medium random
        N = rnd.next(1, 10);
        K = rnd.next(1, 100);
        s.assign(N, 0);
        for (int i = 0; i < N; ++i)
            s[i] = rnd.next(1, K);
        D = rnd.next(1, 100);
    } else if (type == 1) {
        // Moderate sizes, easy to read
        N = rnd.next(2, 8);
        K = rnd.next(3, 30);
        s.assign(N, 0);
        for (int i = 0; i < N; ++i)
            s[i] = rnd.next(1, K);
        D = rnd.next(1, 30);
    } else if (type == 2) {
        // Large D and K
        N = rnd.next(5, 12);
        K = rnd.next(50, 100);
        s.assign(N, 0);
        for (int i = 0; i < N; ++i)
            s[i] = rnd.next(1, K);
        D = rnd.next(50, 100);
    } else if (type == 3) {
        // Force L = 1 (at least one s_i == K)
        N = rnd.next(2, 10);
        K = rnd.next(1, 100);
        s.assign(N, 0);
        int pos = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (i == pos) s[i] = K;
            else s[i] = rnd.next(1, K);
        }
        D = rnd.next(2, 100);
    } else if (type == 4) {
        // One very large s_i, others small (skewed)
        N = rnd.next(2, 10);
        K = rnd.next(20, 100);
        s.assign(N, 0);
        int bigIdx = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (i == bigIdx) {
                int lowBig = K / 2 + 1;
                if (lowBig > K) lowBig = K;
                s[i] = rnd.next(lowBig, K);
            } else {
                int upSmall = max(1, K / 10);
                s[i] = rnd.next(1, upSmall);
            }
        }
        D = rnd.next(2, 100);
    } else if (type == 5) {
        // D is a multiple of L with 2 <= L <= 10 to test boundary behavior
        while (true) {
            N = rnd.next(1, 10);
            K = rnd.next(2, 100);
            s.assign(N, 0);
            for (int i = 0; i < N; ++i)
                s[i] = rnd.next(1, K);
            int L = computeL(K, s);
            if (L >= 2 && L <= 10) {
                int maxM = min(5, 100 / L);
                if (maxM < 1) continue;
                int m = rnd.next(1, maxM);
                D = m * L;
                break;
            }
        }
    }

    println(N, D, K);
    println(s);

    return 0;
}

#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXN = 100000;
    const long long MAXA = 1000000000LL;

    int N;
    int diceN = rnd.next(0, 9);
    if (diceN <= 1) N = rnd.next(2, 10);
    else if (diceN <= 4) N = rnd.next(11, 200);
    else if (diceN <= 7) N = rnd.next(201, 5000);
    else N = rnd.next(5001, MAXN);

    vector<long long> A(N);

    int pattern = rnd.next(0, 9);

    if (pattern == 0) {
        // random small
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1LL, 30LL);

    } else if (pattern == 1) {
        // random wide
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1LL, MAXA);

    } else if (pattern == 2) {
        // increasing
        long long cur = rnd.next(1LL, 20LL);
        for (int i = 0; i < N; ++i) {
            cur += rnd.next(0LL, 20LL);
            A[i] = min(cur, MAXA);
        }

    } else if (pattern == 3) {
        // decreasing
        long long cur = rnd.next(1LL, 1000000LL);
        for (int i = 0; i < N; ++i) {
            A[i] = max(1LL, cur);
            cur -= rnd.next(0LL, max(0LL, cur - 1));
        }

    } else if (pattern == 4) {
        // one huge first, rest small
        A[0] = rnd.next(MAXA / 2, MAXA);
        for (int i = 1; i < N; ++i) A[i] = rnd.next(1LL, 10LL);

    } else if (pattern == 5) {
        // many small, occasional huge spikes
        for (int i = 0; i < N; ++i) {
            if (rnd.next(0, 9) == 0) A[i] = rnd.next(MAXA / 2, MAXA);
            else A[i] = rnd.next(1LL, 20LL);
        }

    } else if (pattern == 6) {
        // alternating small / huge
        for (int i = 0; i < N; ++i) {
            if (i % 2 == 0) A[i] = rnd.next(1LL, 5LL);
            else A[i] = rnd.next(MAXA / 2, MAXA);
        }

    } else if (pattern == 7) {
        // near-prefix style
        A[0] = rnd.next(1LL, 10LL);
        long long pref = A[0];
        for (int i = 1; i < N; ++i) {
            long long add = rnd.next(1LL, 3LL);
            A[i] = min(pref + add, MAXA);
            pref = min(pref + A[i], (long long)4e18);
        }

    } else if (pattern == 8) {
        // best gain appears late
        A[0] = rnd.next(1LL, 20LL);
        long long pref = A[0];
        int pivot = rnd.next(max(2, N / 2), N);
        for (int i = 1; i < N; ++i) {
            if (i + 1 < pivot) {
                long long upper = min(MAXA, max(1LL, pref));
                A[i] = rnd.next(1LL, upper);
            } else if (i + 1 == pivot) {
                A[i] = min(MAXA, pref + rnd.next(100LL, 100000LL));
            } else {
                A[i] = rnd.next(1LL, 100LL);
            }
            pref = min(pref + A[i], (long long)4e18);
        }

    } else {
        // blocks
        int i = 0;
        while (i < N) {
            int len = rnd.next(1, min(100, N - i));
            long long v;
            int type = rnd.next(0, 3);
            if (type == 0) v = rnd.next(1LL, 5LL);
            else if (type == 1) v = rnd.next(10LL, 1000LL);
            else if (type == 2) v = rnd.next(100000LL, 1000000LL);
            else v = rnd.next(MAXA / 2, MAXA);

            for (int j = 0; j < len; ++j) A[i + j] = v;
            i += len;
        }
    }

    // special tweaks
    int special = rnd.next(0, 9);
    if (special == 0) {
        // all ones
        for (int i = 0; i < N; ++i) A[i] = 1;
    } else if (special == 1) {
        // all max
        for (int i = 0; i < N; ++i) A[i] = MAXA;
    } else if (special == 2) {
        // small prefix, then medium repeated
        A[0] = rnd.next(1LL, 10LL);
        for (int i = 1; i < N; ++i) A[i] = rnd.next(1LL, 50LL);
    }

    bool ok = false;
    long long pref = A[0];
    for (int i = 1; i < N; ++i) {
        if (A[i] <= pref) {
            ok = true;
            break;
        }
        pref = min(pref + A[i], (long long)4e18);
    }

    if (!ok) {
        // 가장 간단하게 A[1]을 A[0] 이하로 조정
        A[1] = rnd.next(1LL, A[0]);
    }

    println(N);
    println(A);
    return 0;
}

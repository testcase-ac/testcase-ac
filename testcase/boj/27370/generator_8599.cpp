#include "testlib.h"
using namespace std;

struct TestCase {
    int N;
    int PA;
    int PB;
    vector<int> X;
};

long long absDiffInt(int a, int b) {
    return (a >= b ? (long long)a - b : (long long)b - a);
}

bool genConflictCase(TestCase &out) {
    int maxTries = 100000;
    while (maxTries--) {
        int PA = rnd.next(0, 20);
        int PB = rnd.next(0, 20);
        if (PA == PB) continue;

        int lo = min(PA, PB);
        int hi = max(PA, PB);
        if (hi - lo <= 1) continue; // need room for houses

        int N = rnd.next(2, 5);
        vector<int> X(N);
        for (int i = 0; i < N; ++i) {
            X[i] = rnd.next(lo + 1, hi - 1);
        }

        long long S_min = (1LL << 60);
        long long bestDiffAtS = (1LL << 60);
        long long overallBestDiff = (1LL << 60);

        int totalMasks = 1 << N;
        for (int mask = 0; mask < totalMasks; ++mask) {
            long long sumA = 0;
            long long sumB = 0;
            for (int i = 0; i < N; ++i) {
                long long costA = 2LL * absDiffInt(X[i], PA);
                long long costB = 2LL * absDiffInt(X[i], PB);
                if (mask & (1 << i)) sumA += costA;
                else sumB += costB;
            }
            long long total = sumA + sumB;
            long long diff = sumA >= sumB ? sumA - sumB : sumB - sumA;

            if (total < S_min) {
                S_min = total;
                bestDiffAtS = diff;
            } else if (total == S_min && diff < bestDiffAtS) {
                bestDiffAtS = diff;
            }
            if (diff < overallBestDiff) {
                overallBestDiff = diff;
            }
        }

        if (overallBestDiff < bestDiffAtS) {
            out.N = N;
            out.PA = PA;
            out.PB = PB;
            out.X = X;
            return true;
        }
    }
    return false;
}

TestCase genBasicSmall() {
    TestCase tc;
    int base = rnd.next(0, 50);
    int span = rnd.next(5, 30);
    int PA = base;
    int PB = base + span;
    if (rnd.next(0, 1)) swap(PA, PB);

    int lo = min(PA, PB);
    int hi = max(PA, PB);

    tc.N = rnd.next(1, 8);
    tc.PA = PA;
    tc.PB = PB;
    tc.X.resize(tc.N);
    for (int i = 0; i < tc.N; ++i) {
        tc.X[i] = rnd.next(lo + 1, hi - 1);
    }
    shuffle(tc.X.begin(), tc.X.end());
    return tc;
}

TestCase genAmbiguousHeavy() {
    TestCase tc;
    int base = rnd.next(0, 50);
    // diff even and >=4
    int evenIndex = rnd.next(1, 9); // 1..9 -> diff = 2*(1+idx) = 4..20
    int diff = 2 * (1 + evenIndex); // 4..20
    int P1 = base;
    int P2 = base + diff;
    int PA = P1, PB = P2;
    if (rnd.next(0, 1)) swap(PA, PB);

    int lo = min(PA, PB);
    int hi = max(PA, PB);
    int trueLeft = lo;
    int trueRight = hi;
    int mid = (trueLeft + trueRight) / 2; // integer, since diff is even

    // ambiguous houses at mid
    int ambCnt = rnd.next(1, 5);
    // forced houses
    int leftCnt = rnd.next(0, 3);
    int rightCnt = rnd.next(0, 3);

    vector<int> X;
    for (int i = 0; i < ambCnt; ++i) X.push_back(mid);

    if (mid - trueLeft > 1) {
        for (int i = 0; i < leftCnt; ++i) {
            X.push_back(rnd.next(trueLeft + 1, mid - 1));
        }
    }
    if (trueRight - mid > 1) {
        for (int i = 0; i < rightCnt; ++i) {
            X.push_back(rnd.next(mid + 1, trueRight - 1));
        }
    }

    tc.N = (int)X.size();
    if (tc.N == 0) {
        // fallback: ensure at least one ambiguous
        X.push_back(mid);
        tc.N = 1;
    }
    tc.PA = PA;
    tc.PB = PB;
    shuffle(X.begin(), X.end());
    tc.X = X;
    return tc;
}

TestCase genBoundsCase() {
    TestCase tc;
    int PA, PB;
    if (rnd.next(0, 1) == 0) {
        PA = 0;
        PB = 1000000;
    } else {
        PA = rnd.next(0, 100);
        PB = 1000000 - rnd.next(0, 100);
        if (PA == PB) PB = 1000000;
    }
    if (rnd.next(0, 1)) swap(PA, PB);

    int lo = min(PA, PB);
    int hi = max(PA, PB);

    tc.N = rnd.next(1, 8);
    tc.PA = PA;
    tc.PB = PB;
    tc.X.resize(tc.N);
    for (int i = 0; i < tc.N; ++i) {
        tc.X[i] = rnd.next(lo + 1, hi - 1);
    }
    // introduce some duplicates
    if (tc.N >= 2 && rnd.next(0, 1)) {
        for (int i = 0; i < tc.N / 2; ++i) {
            tc.X[i] = rnd.any(tc.X);
        }
    }
    shuffle(tc.X.begin(), tc.X.end());
    return tc;
}

TestCase genManyDuplicates() {
    TestCase tc;
    int base = rnd.next(0, 50);
    int span = rnd.next(5, 20);
    int PA = base;
    int PB = base + span;
    if (rnd.next(0, 1)) swap(PA, PB);

    int lo = min(PA, PB);
    int hi = max(PA, PB);

    int K = rnd.next(2, 4); // distinct positions
    vector<int> basePos;
    for (int i = 0; i < K; ++i) {
        basePos.push_back(rnd.next(lo + 1, hi - 1));
    }

    tc.N = rnd.next(5, 10);
    tc.PA = PA;
    tc.PB = PB;
    tc.X.resize(tc.N);
    for (int i = 0; i < tc.N; ++i) {
        tc.X[i] = rnd.any(basePos);
    }
    shuffle(tc.X.begin(), tc.X.end());
    return tc;
}

TestCase genRandomMedium() {
    TestCase tc;
    int base = rnd.next(0, 100);
    int span = rnd.next(10, 40);
    int PA = base;
    int PB = base + span;
    if (rnd.next(0, 1)) swap(PA, PB);

    int lo = min(PA, PB);
    int hi = max(PA, PB);

    tc.N = rnd.next(10, 20);
    tc.PA = PA;
    tc.PB = PB;
    tc.X.resize(tc.N);
    for (int i = 0; i < tc.N; ++i) {
        tc.X[i] = rnd.next(lo + 1, hi - 1);
    }
    shuffle(tc.X.begin(), tc.X.end());
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 7);
    vector<TestCase> cases;

    // Try to generate a conflict-case as the first test
    TestCase conflict;
    if (genConflictCase(conflict)) {
        cases.push_back(conflict);
    }

    while ((int)cases.size() < T) {
        int type = rnd.next(0, 4);
        TestCase tc;
        if (type == 0) tc = genBasicSmall();
        else if (type == 1) tc = genAmbiguousHeavy();
        else if (type == 2) tc = genBoundsCase();
        else if (type == 3) tc = genManyDuplicates();
        else tc = genRandomMedium();
        cases.push_back(tc);
    }

    println(T);
    for (int i = 0; i < T; ++i) {
        println(cases[i].N, cases[i].PA, cases[i].PB);
        println(cases[i].X);
    }

    return 0;
}

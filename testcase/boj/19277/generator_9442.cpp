#include "testlib.h"
using namespace std;

struct Query {
    int t, l, r, x;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with several regimes to get variety but keep it small
    int modeN = rnd.next(0, 3);
    int N;
    if (modeN == 0) N = rnd.next(1, 3);
    else if (modeN == 1) N = rnd.next(4, 7);
    else if (modeN == 2) N = rnd.next(8, 12);
    else N = rnd.next(13, 15);

    // Choose Q relative to N, but still small enough to read
    int Qlo = max(1, N / 2);
    int Qhi = 4 * N + 3;
    int Q = rnd.next(Qlo, Qhi);

    // Initial array scenarios
    int scenArr = rnd.next(0, 4);
    vector<int> a(N);
    if (scenArr == 0) {
        // random small values
        for (int i = 0; i < N; ++i) a[i] = rnd.next(0, 20);
    } else if (scenArr == 1) {
        // all zeros
        for (int i = 0; i < N; ++i) a[i] = 0;
    } else if (scenArr == 2) {
        // increasing arithmetic progression
        int base = rnd.next(0, 10);
        int step = rnd.next(0, 5);
        for (int i = 0; i < N; ++i) a[i] = base + step * i;
    } else if (scenArr == 3) {
        // random over full allowed range
        for (int i = 0; i < N; ++i) a[i] = rnd.next(0, 100000000);
    } else {
        // alternating small / big
        int small = rnd.next(0, 10);
        int big = rnd.next(50000000, 100000000);
        bool startBig = rnd.next(0, 1);
        for (int i = 0; i < N; ++i) {
            bool useBig = ((i % 2) == 0 ? startBig : !startBig);
            a[i] = useBig ? big : small;
        }
    }

    // Hyper-parameters for query generation
    int styleType = rnd.next(0, 3);  // distribution of t
    int rangeMode = rnd.next(0, 3);  // distribution of ranges
    int addStyle  = rnd.next(0, 3);  // distribution of ADD x

    auto randRange = [&]() -> pair<int,int> {
        if (N == 1) return {0, 0};
        int l = rnd.next(0, N - 1);
        int r = rnd.next(l, N - 1);
        return {l, r};
    };

    auto chooseRange = [&]() -> pair<int,int> {
        if (N == 1) return {0, 0};

        int l, r;
        if (rangeMode == 0) {
            // mostly point updates/queries
            if (rnd.next(0, 99) < 70) {
                int idx = rnd.next(0, N - 1);
                return {idx, idx};
            } else {
                return randRange();
            }
        } else if (rangeMode == 1) {
            // mostly full range
            if (rnd.next(0, 99) < 70) {
                return {0, N - 1};
            } else {
                return randRange();
            }
        } else if (rangeMode == 2) {
            // fully random
            return randRange();
        } else {
            // mixture: randomly choose among point / full / random
            int m = rnd.next(0, 2);
            if (m == 0) {
                int idx = rnd.next(0, N - 1);
                return {idx, idx};
            } else if (m == 1) {
                return {0, N - 1};
            } else {
                return randRange();
            }
        }
    };

    auto chooseType = [&]() -> int {
        int r = rnd.next(0, 99);
        if (styleType == 0) {
            // mixed: 40% ADD, 30% DIV, 30% MAX
            if (r < 40) return 0;
            else if (r < 70) return 1;
            else return 2;
        } else if (styleType == 1) {
            // DIV-heavy: 20% ADD, 60% DIV, 20% MAX
            if (r < 20) return 0;
            else if (r < 80) return 1;
            else return 2;
        } else if (styleType == 2) {
            // ADD-heavy: 60% ADD, 20% DIV, 20% MAX
            if (r < 60) return 0;
            else if (r < 80) return 1;
            else return 2;
        } else {
            // MAX-heavy: 30% ADD, 20% DIV, 50% MAX
            if (r < 30) return 0;
            else if (r < 50) return 1;
            else return 2;
        }
    };

    auto chooseAddX = [&]() -> int {
        if (addStyle == 0) {
            // small increments
            return rnd.next(1, 5);
        } else if (addStyle == 1) {
            // medium increments
            return rnd.next(1, 100);
        } else if (addStyle == 2) {
            // large increments
            return rnd.next(500, 1000);
        } else {
            // mixture
            int s = rnd.next(0, 2);
            if (s == 0) return rnd.next(1, 5);
            if (s == 1) return rnd.next(1, 100);
            return rnd.next(500, 1000);
        }
    };

    auto chooseDivX = [&]() -> int {
        int r = rnd.next(0, 99);
        if (r < 30) {
            // many x=1 (no-op but stresses structure)
            return 1;
        } else if (r < 50) {
            return 2;
        } else if (r < 70) {
            return rnd.next(3, 5);
        } else if (r < 80) {
            return rnd.next(6, 10);
        } else {
            return rnd.next(11, 1000);
        }
    };

    vector<Query> qs(Q);

    // Ensure some deterministic, easy-to-read initial operations if possible
    int idx = 0;
    if (Q >= 1) {
        qs[0] = {2, 0, N - 1, 0}; // MAX over whole range
        idx = 1;
    }
    if (Q >= 2) {
        qs[1] = {0, 0, N - 1, rnd.next(1, 1000)}; // ADD over whole range
        idx = 2;
    }
    if (Q >= 3) {
        qs[2] = {1, 0, N - 1, 2}; // DIV by 2 over whole range
        idx = 3;
    }

    for (int i = idx; i < Q; ++i) {
        int t = chooseType();
        auto pr = chooseRange();
        int l = pr.first, r = pr.second;
        int x;
        if (t == 2) {
            x = 0;
        } else if (t == 0) {
            x = chooseAddX();
        } else {
            x = chooseDivX();
        }
        qs[i] = {t, l, r, x};
    }

    // Output
    println(N, Q);
    println(a);
    for (int i = 0; i < Q; ++i) {
        println(qs[i].t, qs[i].l, qs[i].r, qs[i].x);
    }

    return 0;
}

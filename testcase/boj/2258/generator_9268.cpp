#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LIM = 2147483647;
    int scenario = rnd.next(1, 6);

    int N = 0;
    int M = 1;
    vector<pair<int, int>> a;

    if (scenario == 1) {
        // Small random case
        N = rnd.next(1, 6);
        long long sumW = 0;
        for (int i = 0; i < N; ++i) {
            int w = rnd.next(0, 10);
            int p = rnd.next(0, 10);
            a.push_back({w, p});
            sumW += w;
        }
        if (sumW > 0 && rnd.next(0, 1) == 0) {
            // Make it possible
            M = rnd.next(1, (int)sumW);
        } else {
            // Likely impossible
            long long lo = sumW + 1;
            long long hi = sumW + 20;
            if (hi < lo) hi = lo;
            M = (int)lo;
            if (hi > lo) M = rnd.next((int)lo, (int)hi);
        }
        shuffle(a.begin(), a.end());
    } else if (scenario == 2) {
        // Medium random with varied bounds
        N = rnd.next(5, 15);
        int maxW = rnd.next(5, 40);
        int maxP = rnd.next(5, 40);
        long long sumW = 0;
        for (int i = 0; i < N; ++i) {
            int w = rnd.next(0, maxW);
            int p = rnd.next(0, maxP);
            a.push_back({w, p});
            sumW += w;
        }
        if (sumW > 0 && rnd.next(0, 1) == 0) {
            M = rnd.next(1, (int)sumW);
        } else {
            long long lo = sumW + 1;
            long long hi = sumW + 20;
            if (hi < lo) hi = lo;
            M = (int)lo;
            if (hi > lo) M = rnd.next((int)lo, (int)hi);
        }
        int order = rnd.next(0, 2);
        if (order == 0) {
            shuffle(a.begin(), a.end());
        } else if (order == 1) {
            sort(a.begin(), a.end(),
                 [](const pair<int, int>& x, const pair<int, int>& y) {
                     if (x.second != y.second) return x.second < y.second;
                     return x.first < y.first;
                 });
        } else {
            sort(a.begin(), a.end(),
                 [](const pair<int, int>& x, const pair<int, int>& y) {
                     if (x.second != y.second) return x.second > y.second;
                     return x.first > y.first;
                 });
        }
    } else if (scenario == 3) {
        // One high-price group, many cheaper ones
        N = rnd.next(3, 12);
        int cheapCnt = rnd.next(1, N - 1);
        int expensiveCnt = N - cheapCnt;

        int highP = rnd.next(2, 20); // at least 2 so we have cheaper prices
        int lowPmax = rnd.next(0, highP - 1);

        long long sumW = 0;
        // Cheaper group
        for (int i = 0; i < cheapCnt; ++i) {
            int p = rnd.next(0, lowPmax);
            int w = rnd.next(0, 20);
            a.push_back({w, p});
            sumW += w;
        }
        // Expensive group (all same price)
        for (int i = 0; i < expensiveCnt; ++i) {
            int p = highP;
            int w = rnd.next(1, 30);
            a.push_back({w, p});
            sumW += w;
        }

        if (sumW > 0 && rnd.next(0, 1) == 0) {
            M = rnd.next(1, (int)sumW);
        } else {
            long long lo = sumW + 1;
            long long hi = sumW + 20;
            if (hi < lo) hi = lo;
            M = (int)lo;
            if (hi > lo) M = rnd.next((int)lo, (int)hi);
        }

        int style = rnd.next(0, 2);
        if (style == 0) {
            shuffle(a.begin(), a.end());
        } else if (style == 1) {
            sort(a.begin(), a.end(),
                 [](const pair<int, int>& x, const pair<int, int>& y) {
                     if (x.second != y.second) return x.second < y.second;
                     return x.first < y.first;
                 });
        } // else keep cheap then expensive order
    } else if (scenario == 4) {
        // Many zero-price or zero-weight pieces
        N = rnd.next(3, 10);
        long long sumW = 0;
        long long sumZeroPriceW = 0;
        for (int i = 0; i < N; ++i) {
            int p = (rnd.next(0, 2) == 0) ? 0 : rnd.next(1, 15);
            int w = (rnd.next(0, 2) == 0) ? 0 : rnd.next(1, 15);
            a.push_back({w, p});
            sumW += w;
            if (p == 0) sumZeroPriceW += w;
        }

        if (sumW == 0) {
            M = rnd.next(1, 30); // impossible
        } else {
            int mode = rnd.next(0, 2);
            if (mode == 0 && sumZeroPriceW > 0) {
                // Only zero-price meats are enough -> optimal cost 0
                M = rnd.next(1, (int)sumZeroPriceW);
            } else if (mode == 1 && sumZeroPriceW < sumW) {
                // Need some positive-price meats
                int lo = (int)max(sumZeroPriceW + 1, 1LL);
                int hi = (int)sumW;
                if (lo > hi) lo = 1;
                M = rnd.next(lo, hi);
            } else {
                // Impossible
                long long lo = sumW + 1;
                long long hi = sumW + 20;
                if (hi < lo) hi = lo;
                M = (int)lo;
                if (hi > lo) M = rnd.next((int)lo, (int)hi);
            }
        }
        shuffle(a.begin(), a.end());
    } else if (scenario == 5) {
        // Strictly increasing prices
        N = rnd.next(3, 12);
        long long sumW = 0;
        int curP = rnd.next(0, 5);
        for (int i = 0; i < N; ++i) {
            curP += rnd.next(1, 5); // strictly increasing
            int w = rnd.next(0, 25);
            a.push_back({w, curP});
            sumW += w;
        }

        if (sumW > 0 && rnd.next(0, 1) == 0) {
            M = rnd.next(1, (int)sumW);
        } else {
            long long lo = sumW + 1;
            long long hi = sumW + 20;
            if (hi < lo) hi = lo;
            M = (int)lo;
            if (hi > lo) M = rnd.next((int)lo, (int)hi);
        }

        if (rnd.next(0, 1) == 0) {
            // Keep ascending by price
        } else {
            reverse(a.begin(), a.end()); // descending by price
        }
    } else if (scenario == 6) {
        // Big numbers near limits to test overflow handling
        N = rnd.next(1, 5);
        long long remainingW = LIM;
        long long remainingP = LIM;
        long long sumW = 0;

        for (int i = 0; i < N; ++i) {
            int maxWi = (int)min(1000000000LL, remainingW);
            if (maxWi < 0) maxWi = 0;
            int w = rnd.next(0, maxWi);
            remainingW -= w;
            sumW += w;

            int maxPi = (int)min(1000000000LL, remainingP);
            if (maxPi < 0) maxPi = 0;
            int p = rnd.next(0, maxPi);
            remainingP -= p;

            a.push_back({w, p});
        }

        if (sumW == 0) {
            M = rnd.next(1, LIM); // impossible
        } else {
            if (rnd.next(0, 1) == 0) {
                int hi = (int)min(sumW, (long long)LIM);
                M = rnd.next(1, hi); // possible
            } else if (sumW < LIM) {
                int lo = (int)(sumW + 1);
                int hi = LIM;
                M = rnd.next(lo, hi); // impossible
            } else {
                // sumW == LIM, only possible case
                M = rnd.next(1, LIM);
            }
        }
        shuffle(a.begin(), a.end());
    }

    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(a[i].first, a[i].second);
    }

    return 0;
}

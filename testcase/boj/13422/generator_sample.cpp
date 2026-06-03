#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long windowSum(const vector<int>& money, int start, int len) {
    long long sum = 0;
    int n = (int)money.size();
    for (int i = 0; i < len; ++i) {
        sum += money[(start + i) % n];
    }
    return sum;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(4, 12);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int N = rnd.next(1, 18);
        int M = rnd.next(1, N);
        vector<int> money(N);

        if (mode == 0) {
            M = N;
            int hi = rnd.next(1, 25);
            for (int& x : money) x = rnd.next(1, hi);
        } else if (mode == 1) {
            M = 1;
            int pivot = rnd.next(1, 30);
            for (int& x : money) x = rnd.next(max(1, pivot - 3), pivot + 3);
        } else if (mode == 2) {
            N = rnd.next(2, 18);
            M = rnd.next(max(1, N - 4), N);
            money.assign(N, 1);
            int spikes = rnd.next(1, min(N, 4));
            for (int i = 0; i < spikes; ++i) {
                money[rnd.next(0, N - 1)] = rnd.next(20, 80);
            }
        } else if (mode == 3) {
            int value = rnd.next(1, 40);
            fill(money.begin(), money.end(), value);
        } else if (mode == 4) {
            int lo = rnd.next(1, 10);
            int hi = rnd.next(lo, lo + 20);
            for (int& x : money) x = rnd.next(lo, hi);
            sort(money.begin(), money.end());
            if (rnd.next(0, 1)) reverse(money.begin(), money.end());
        } else {
            for (int i = 0; i < N; ++i) {
                money[i] = (i % 2 == 0) ? rnd.next(1, 8) : rnd.next(30, 90);
            }
            shuffle(money.begin(), money.end());
        }

        vector<long long> sums;
        int windows = (N == M) ? 1 : N;
        for (int i = 0; i < windows; ++i) {
            sums.push_back(windowSum(money, i, M));
        }

        long long minSum = *min_element(sums.begin(), sums.end());
        long long maxSum = *max_element(sums.begin(), sums.end());
        long long K;
        int kMode = rnd.next(0, 5);
        if (kMode == 0) {
            K = max(1LL, minSum);
        } else if (kMode == 1) {
            K = minSum + 1;
        } else if (kMode == 2) {
            K = maxSum;
        } else if (kMode == 3) {
            K = maxSum + 1;
        } else if (kMode == 4) {
            K = rnd.any(sums);
        } else {
            K = rnd.next(1LL, max(1LL, maxSum + 5));
        }
        K = min(K, 1000000000LL);

        println(N, M, K);
        println(money);
    }

    return 0;
}

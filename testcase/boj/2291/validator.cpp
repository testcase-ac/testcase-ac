#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const long long LIMIT = 2147483647LL;

long long countSequences(int remaining, int sum, int minValue,
                         vector<vector<vector<long long>>>& memo) {
    if (remaining == 0) {
        return sum == 0 ? 1 : 0;
    }
    if (sum < remaining * minValue) {
        return 0;
    }

    long long& cached = memo[remaining][sum][minValue];
    if (cached != -1) {
        return cached;
    }

    long long total = 0;
    int maxValue = sum / remaining;
    for (int value = minValue; value <= maxValue; ++value) {
        total += countSequences(remaining - 1, sum - value, value, memo);
        if (total > LIMIT) {
            total = LIMIT + 1;
            break;
        }
    }

    cached = total;
    return cached;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 220, "M");
    inf.readSpace();
    int K = inf.readInt(1, 2147483647, "K");
    inf.readEoln();

    ensuref(M >= N, "Sum M=%d is too small for N=%d (all Ai >= 1)", M, N);

    vector<vector<vector<long long>>> memo(
        N + 1, vector<vector<long long>>(M + 1, vector<long long>(M + 1, -1)));
    long long total = countSequences(N, M, 1, memo);

    ensuref(total >= K, "There are only %lld valid sequences, but K=%d", total, K);

    inf.readEof();
}

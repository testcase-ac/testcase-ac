#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<long long> subsetSums(const vector<long long>& values) {
    vector<long long> sums;
    sums.reserve(1ULL << values.size());
    sums.push_back(0);
    for (long long value : values) {
        int currentSize = static_cast<int>(sums.size());
        for (int i = 0; i < currentSize; ++i) {
            sums.push_back(sums[i] + value);
        }
    }
    sort(sums.begin(), sums.end());
    return sums;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 40, "n");
    inf.readEoln();

    vector<long long> a(n);
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong(1LL, 2000000000LL, "a_i");
        inf.readEoln();
        total += a[i];
        ensuref(total <= 2000000000LL, "sum of a_i exceeds 2000000000");
    }

    long long k = inf.readLong(0LL, total, "K");
    inf.readEoln();
    inf.readEof();

    vector<long long> leftValues(a.begin(), a.begin() + n / 2);
    vector<long long> rightValues(a.begin() + n / 2, a.end());
    vector<long long> left = subsetSums(leftValues);
    vector<long long> right = subsetSums(rightValues);

    long long solutions = 0;
    for (long long leftSum : left) {
        auto range = equal_range(right.begin(), right.end(), k - leftSum);
        solutions += range.second - range.first;
        ensuref(solutions <= 1, "encrypted message is not uniquely determined");
    }
    ensuref(solutions == 1, "encrypted message has no valid decryption");
}

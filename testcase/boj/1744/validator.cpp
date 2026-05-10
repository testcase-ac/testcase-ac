#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 <= N < 50
    int N = inf.readInt(1, 49, "N");
    inf.readEoln();

    vector<int> positives;
    vector<int> negatives;
    int64_t ones = 0;
    int64_t zeros = 0;

    // Read sequence values
    for (int i = 0; i < N; i++) {
        char name[20];
        sprintf(name, "x_%d", i+1);
        int x = inf.readInt(-1000, 1000, name);
        inf.readEoln();
        if (x > 1) {
            positives.push_back(x);
        } else if (x == 1) {
            ones++;
        } else if (x == 0) {
            zeros++;
        } else {
            negatives.push_back(x);
        }
    }

    // Compute maximum sum by optimal pairing
    int64_t total = 0;

    // Add all ones directly
    total += ones;

    // Handle positives > 1: sort descending, pair greedily
    sort(positives.begin(), positives.end(), greater<int>());
    int p_sz = positives.size();
    for (int i = 0; i + 1 < p_sz; i += 2) {
        total += (int64_t)positives[i] * positives[i+1];
    }
    if (p_sz % 2 == 1) {
        total += positives.back();
    }

    // Handle negatives: sort ascending (more negative first), pair greedily
    sort(negatives.begin(), negatives.end());
    int n_sz = negatives.size();
    for (int i = 0; i + 1 < n_sz; i += 2) {
        total += (int64_t)negatives[i] * negatives[i+1];
    }
    if (n_sz % 2 == 1) {
        // one negative left unpaired
        if (zeros > 0) {
            // pair it with zero gives zero contribution
        } else {
            total += negatives.back();
        }
    }

    // Check global property: answer must be < 2^31
    const int64_t LIMIT = (1LL << 31);
    ensuref(total < LIMIT,
            "Computed answer %lld is not less than 2^31", total);

    inf.readEof();
    return 0;
}

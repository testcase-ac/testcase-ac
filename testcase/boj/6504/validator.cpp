#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Precompute Fibonacci numbers as defined in the problem:
    // F1 = 1, F2 = 2, Fn+1 = Fn + F_{n-1}
    // We only need up to values > 25000 (max x) to safely represent any x, and
    // up to roughly 2*x to be safe for simulation of y, still very small.
    vector<int> F;
    F.push_back(0); // dummy for 1-based indexing
    F.push_back(1); // F1
    F.push_back(2); // F2
    while (true) {
        int n = (int)F.size() - 1;
        long long nxt = (long long)F[n] + (long long)F[n - 1];
        if (nxt > 100000) break; // well above any needed bound
        F.push_back((int)nxt);
    }
    int maxFibIndex = (int)F.size() - 1;

    int t = inf.readInt(1, 24999, "t");
    inf.readEoln();

    for (int caseId = 0; caseId < t; ++caseId) {
        int x = inf.readInt(3, 24999, "x"); // 2 < x < 25000
        inf.readEoln();

        // --- Validate the implied property:
        // Every positive integer X has a unique Fibonacci representation
        // with no consecutive 1s, using the given Fibonacci sequence.
        // We also need to ensure the algorithm's y always exists and is positive.

        // Step 1: Compute the Fibonacci representation b(x) with constraint
        // "no consecutive 1 bits", using greedy algorithm (Zeckendorf-like).
        // Find largest index k with F[k] <= x.
        int k = 1;
        while (k + 1 <= maxFibIndex && F[k + 1] <= x) ++k;

        vector<int> b(k + 1, 0); // 1..k used
        int remaining = x;
        int lastUsed = 0;
        for (int i = k; i >= 1; --i) {
            if (F[i] <= remaining && lastUsed == 0) {
                b[i] = 1;
                remaining -= F[i];
                lastUsed = 1;
            } else {
                b[i] = 0;
                if (lastUsed == 1) lastUsed = 0;
            }
        }
        ensuref(remaining == 0, "Failed to represent x=%d as sum of distinct Fibonacci numbers", x);

        // Additionally, check no consecutive ones condition explicitly
        for (int i = 2; i <= k; ++i) {
            ensuref(!(b[i] == 1 && b[i - 1] == 1),
                    "Consecutive Fibonacci digits 1 found in representation of x=%d", x);
        }

        // Step 2: Apply Sang-geun's algorithm:
        // Right-shift b(x) by one (drop the last bit) to obtain b(y).
        // Original b(x) = (b_k, ..., b_1). After shift: (b_k, ..., b_2).
        // That is, we drop index 1 and keep indices 2..k with same positions.
        long long y = 0;
        for (int i = 2; i <= k; ++i) {
            if (b[i]) y += F[i - 1]; // shifted: bit at i contributes F_{i-1}
        }

        // y must be positive integer since x > 2 and at least F2=2 is in sequence.
        ensuref(y >= 1, "Converted miles y is not positive for x=%d (y=%lld)", x, y);
        ensuref(y <= 100000, "Converted miles y too large for x=%d (y=%lld)", x, y);
    }

    inf.readEof();
}

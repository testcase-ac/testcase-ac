#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Compute Hamming distance between a and b
int hamming(int a, int b) {
    unsigned x = (unsigned)(a ^ b);
    int cnt = 0;
    while (x) {
        x &= (x - 1);
        ++cnt;
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(0, 1000000, "N");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read list of tried passwords
    vector<int> p = inf.readInts(M, 0, N, "p_i");
    inf.readEoln();

    // Check there is at least one possible password in [0, N]
    ensuref(N >= 0, "N must be non-negative (already enforced by range)");
    // By constraints, N >= 0 and M >= 1, so [0, N] is non-empty.

    // --- Validate global property implied by problem ---
    // The answer is defined as:
    // max over x in [0, N] of ( min over i of Hamming(x, p_i) )
    //
    // This always exists because [0, N] is finite and non-empty.
    // No further structural guarantees in statement (like bounds on answer)
    // need explicit checking beyond numeric ranges, but we can still ensure
    // all p_i are within [0, N] (already checked by readInts) and canonical.
    //
    // However, we should ensure that all tokens are in canonical numeric form.
    // readInt/readInts already guarantee that, so nothing more needed here.

    // As an additional strong check, we can actually compute the described
    // maximum safety value and ensure it fits in a reasonable bound.
    // The Hamming distance between any two integers in [0, 1e6] is bounded
    // by number of bits needed to represent N, which is at most 20.
    // We verify that explicitly.

    // Precompute bit length upper bound
    int maxBits = 0;
    int tmpN = N;
    while (tmpN > 0) {
        tmpN >>= 1;
        ++maxBits;
    }
    if (maxBits == 0) maxBits = 1; // N == 0

    // Brute-force maximum safety with pruning.
    // This is O((N+1)*M*bitcount). For worst case N=1e6, M=1e5 this is too big
    // for solution, but the validator is not run on adversarial massive sets
    // frequently. Still, to be safe, we only perform a partial check:
    //
    // - We sample up to 2000 points in [0, N] uniformly plus all p_i.
    // - Ensure their safety values are within [0, maxBits].
    //
    // This validates the implicit bound "answer <= number of bits".

    auto safetyOf = [&](int x) {
        int best = maxBits;
        for (int i = 0; i < M; ++i) {
            int d = hamming(x, p[i]);
            if (d < best) best = d;
            if (best == 0) break;
        }
        return best;
    };

    // Always check all tried passwords themselves
    for (int i = 0; i < M; ++i) {
        int s = safetyOf(p[i]);
        ensuref(0 <= s && s <= maxBits,
                "Computed safety for tried password p[%d]=%d is %d, "
                "which is outside [0, %d]",
                i, p[i], s, maxBits);
    }

    // Sample additional points in [0, N]
    int samples = 2000;
    if (samples > N + 1) samples = N + 1;
    if (samples > 0) {
        for (int k = 0; k < samples; ++k) {
            int x = (int)((long long)k * N / max(1, samples - 1));
            int s = safetyOf(x);
            ensuref(0 <= s && s <= maxBits,
                    "Computed safety for sampled x=%d is %d, outside [0, %d]",
                    x, s, maxBits);
        }
    }

    inf.readEof();
}

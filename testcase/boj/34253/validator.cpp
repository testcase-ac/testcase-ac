#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 20, "K");
    inf.readEoln();

    // We will simulate the classification (WellKnown / AdHoc)
    // to ensure that the assumptions in the statement always hold.
    //
    // Model:
    // - There are K algorithms, numbered 1..K.
    // - Each problem i is represented by a subset of these algorithms.
    //   Because of the encoding rule, we must decode S_i depending on z_i.
    // - z_1 = 0. For i > 1, z_i = 0 iff problem i-1 is WellKnown, else 1.
    // - "Problem B is WellKnown if there exists some earlier problem A
    //    such that alg(A) is a superset of alg(B)."
    //
    // We maintain a boolean array of size 2^K indicating whether a
    // specific subset of algorithms has appeared before.
    // To check if current mask is WellKnown, we check if any superset
    // mask' of mask is marked as seen.
    //
    // This is O(N * 2^(K - popcount(mask))) worst-case 2^K per query,
    // which is fine for K <= 20 and N <= 3e5 in a validator context.

    int maxMask = 1 << K;
    vector<char> seen(maxMask, 0);

    auto isWellKnown = [&](int mask) -> bool {
        // Enumerate all supersets of mask within K bits.
        // Standard technique: iterate over submask of the complement
        // and OR with mask.
        int complement = ((1 << K) - 1) ^ mask;
        int sub = complement;
        while (true) {
            int sup = mask | sub;
            if (seen[sup]) return true;
            if (sub == 0) break;
            sub = (sub - 1) & complement;
        }
        return false;
    };

    int zi = 0; // z_1 = 0

    for (int i = 1; i <= N; ++i) {
        // Read S_i: length K, only '0' and '1'
        string s = inf.readToken("[01]{1,20}", "S_i");
        inf.readEoln();

        ensuref((int)s.size() == K,
                "S_%d must have length exactly K=%d, got %d", i, K, (int)s.size());

        // Decode to bitmask according to z_i
        int mask = 0;
        if (zi == 0) {
            // direct: j-th char (0-based) corresponds to algorithm j+1
            for (int j = 0; j < K; ++j) {
                if (s[j] == '1')
                    mask |= (1 << j);
                else
                    ensuref(s[j] == '0', "S_%d contains invalid character", i);
            }
        } else {
            // reversed: (K-j)-th char (1-based) => s[K-j] (0-based)
            for (int j = 0; j < K; ++j) {
                char c = s[K - 1 - j];
                if (c == '1')
                    mask |= (1 << j);
                else
                    ensuref(c == '0', "S_%d contains invalid character", i);
            }
        }

        // Determine WellKnown / AdHoc
        bool well = isWellKnown(mask);
        // Update z_(i+1)
        zi = well ? 0 : 1;
        // Mark current set as seen for future problems
        seen[mask] = 1;
    }

    inf.readEof();
}

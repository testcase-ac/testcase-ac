#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(5, 1000, "N");
    inf.readEoln();

    // 2. Read N numbers, check constraints and uniqueness
    vector<int> U;
    set<int> seen;
    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(1, 200000000, "U_i");
        inf.readEoln();
        ensuref(seen.count(x) == 0, "Duplicate element detected at index %d: %d", i+1, x);
        seen.insert(x);
        U.push_back(x);
    }

    // 3. Check that answer always exists (as per statement)
    //    That is, there exists i, j, k, l (indices, possibly not all distinct)
    //    such that U[i] + U[j] + U[k] == U[l]
    //    We must check that at least one such quadruple exists.

    // For efficient lookup, use unordered_set
    unordered_set<int> Uset(U.begin(), U.end());

    bool found = false;
    // Since N <= 1000, O(N^3) is feasible (1e9 at worst, but we can optimize)
    // Let's sort U for possible optimizations
    sort(U.begin(), U.end());
    for (int l = 0; l < N && !found; ++l) {
        int d = U[l];
        // Try to find i, j, k such that U[i] + U[j] + U[k] == d
        // Since x, y, z, k can be same (indices can be same), we can do:
        // For all i, j, k in [0, N)
        for (int i = 0; i < N && !found; ++i) {
            for (int j = 0; j < N && !found; ++j) {
                for (int k = 0; k < N && !found; ++k) {
                    long long sum = 1LL * U[i] + U[j] + U[k];
                    if (sum == d) {
                        found = true;
                    }
                }
            }
        }
    }
    ensuref(found, "No triple (i, j, k) such that U[i] + U[j] + U[k] == U[l] for some l. The answer must always exist according to the problem statement.");

    inf.readEof();
}

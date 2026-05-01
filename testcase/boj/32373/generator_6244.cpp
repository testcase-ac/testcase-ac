#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate sequence length N
    int N = rnd.next(2, 25);
    // Hyper-parameter for skewed k: small, medium, large
    int t_choice = rnd.any(vector<int>{-2, 0, 2});
    // rnd.wnext(N-1, t_choice) gives [0..N-2], so +1 => k in [1..N-1]
    int k = rnd.wnext(N - 1, t_choice) + 1;

    // Build classes by residue mod k for values and positions
    vector<vector<int>> cls(k), pos(k);
    for (int v = 0; v < N; v++)
        cls[v % k].push_back(v);
    for (int i = 1; i <= N; i++)
        pos[(i - 1) % k].push_back(i);

    // Prepare an array A[1..N]
    vector<int> A(N + 1);
    // Assign a valid permutation: shuffle within each class
    for (int r = 0; r < k; r++) {
        shuffle(cls[r].begin(), cls[r].end());
        for (size_t j = 0; j < pos[r].size(); j++) {
            int p = pos[r][j];
            A[p] = cls[r][j];
        }
    }

    // Decide if we create an invalid case (only possible if k > 1)
    bool makeValid = (k == 1) || (rnd.next(0, 9) < 7);
    if (!makeValid) {
        // Pick two distinct non-empty classes and swap one element each
        vector<int> nonEmpty;
        for (int r = 0; r < k; r++)
            if (!pos[r].empty())
                nonEmpty.push_back(r);
        if (nonEmpty.size() >= 2) {
            int r1 = rnd.any(nonEmpty);
            int r2 = rnd.any(nonEmpty);
            while (r2 == r1)
                r2 = rnd.any(nonEmpty);
            int p1 = rnd.any(pos[r1]);
            int p2 = rnd.any(pos[r2]);
            swap(A[p1], A[p2]);
        }
    }

    // Output result
    println(N, k);
    vector<int> out(N);
    for (int i = 1; i <= N; i++)
        out[i - 1] = A[i];
    println(out);

    return 0;
}

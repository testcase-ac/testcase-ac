#include "testlib.h"
using namespace std;

struct Op {
    int type; // 1 = merge, 2 = query
    int a;
    int b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 3);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int N = rnd.next(1, 10);
        int maxL = min(2 * N, 20);
        int L = rnd.next(1, maxL);

        int maxMergeByN = N / 2;
        int maxMergeByL = (L >= 1 ? L - 1 : 0);
        int maxMerges = min(maxMergeByN, maxMergeByL);

        int mergesCnt = 0;
        if (maxMerges > 0) {
            int biasOptions[3] = {-3, 0, 3};
            int bias = biasOptions[rnd.next(0, 2)];
            mergesCnt = rnd.wnext(maxMerges + 1, bias);
            if (mergesCnt > maxMerges) mergesCnt = maxMerges;
        }

        int queriesCnt = L - mergesCnt;
        if (queriesCnt == 0) {
            // Ensure at least one query
            if (mergesCnt > 0) {
                --mergesCnt;
                ++queriesCnt;
            } else {
                queriesCnt = 1;
            }
        }
        // Final L is determined by actual counts
        L = mergesCnt + queriesCnt;

        vector<Op> ops;

        // Prepare merges: each group index is used in at most one merge (any side).
        // This guarantees merges are valid regardless of which parameter
        // the validator considers as the "from" (dead) group.
        vector<int> remGroups(N);
        for (int i = 0; i < N; ++i) remGroups[i] = i + 1;

        for (int i = 0; i < mergesCnt; ++i) {
            if ((int)remGroups.size() < 2) break;

            int idx1 = rnd.next(0, (int)remGroups.size() - 1);
            int g1 = remGroups[idx1];
            remGroups[idx1] = remGroups.back();
            remGroups.pop_back();

            int idx2 = rnd.next(0, (int)remGroups.size() - 1);
            int g2 = remGroups[idx2];
            remGroups[idx2] = remGroups.back();
            remGroups.pop_back();

            int X, Y;
            if (rnd.next(0, 1) == 0) {
                X = g1; Y = g2;
            } else {
                X = g2; Y = g1;
            }
            ops.push_back({1, X, Y});
        }

        // Adjust counts in case we created fewer merges due to lack of groups
        mergesCnt = 0;
        for (auto &op : ops) if (op.type == 1) ++mergesCnt;
        queriesCnt = L - mergesCnt;
        if (queriesCnt <= 0) {
            queriesCnt = 1;
            L = mergesCnt + queriesCnt;
        }

        // Generate queries
        for (int i = 0; i < queriesCnt; ++i) {
            int J;
            if (N == 1) {
                J = 1;
            } else {
                int biasChoice = rnd.next(0, 2);
                int t = 0;
                if (biasChoice == 0) t = -3;      // favor small indices
                else if (biasChoice == 2) t = 3;  // favor large indices

                if (t == 0) {
                    J = rnd.next(1, N);
                } else {
                    int idx = rnd.wnext(N, t); // [0..N-1]
                    if (idx < 0) idx = 0;
                    if (idx >= N) idx = N - 1;
                    J = idx + 1;
                }
            }
            ops.push_back({2, J, 0});
        }

        // Shuffle operations to interleave merges and queries
        shuffle(ops.begin(), ops.end());

        // Output test case
        println(N, (int)ops.size());
        for (const Op &op : ops) {
            if (op.type == 1) {
                println(1, op.a, op.b);
            } else {
                println(2, op.a);
            }
        }
    }

    return 0;
}

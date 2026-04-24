#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 ≤ T ≤ 100000 (not specified in statement, so assume up to 1e5)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Number of nodes in this test: 1 ≤ n ≤ 1000
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        // Preorder sequence: n integers, each in [1, n]
        vector<int> preorder = inf.readInts(n, 1, n, "preorder");
        inf.readEoln();

        // Inorder sequence: n integers, each in [1, n]
        vector<int> inorder = inf.readInts(n, 1, n, "inorder");
        inf.readEoln();

        // Check that both are permutations of [1..n] and that they match as multisets
        vector<int> cnt(n+1, 0);
        for (int i = 0; i < n; i++) {
            int x = preorder[i];
            ensuref(cnt[x] == 0,
                    "Duplicate value %d in preorder at test case %d, position %d", 
                    x, tc, i+1);
            cnt[x]++;
        }
        for (int i = 0; i < n; i++) {
            int x = inorder[i];
            ensuref(cnt[x] == 1,
                    "Value %d in inorder at test case %d, position %d does not match preorder", 
                    x, tc, i+1);
            cnt[x]--;
        }
        for (int x = 1; x <= n; x++) {
            ensuref(cnt[x] == 0,
                    "Value %d missing in inorder at test case %d", 
                    x, tc);
        }
    }

    inf.readEof();
    return 0;
}

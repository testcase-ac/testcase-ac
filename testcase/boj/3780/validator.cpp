#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

static const int MAX_TESTS = 100000;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) {
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    void unite_root_to(int rootA, int rootB) {
        // make rootB the parent of rootA
        p[rootA] = rootB;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, MAX_TESTS, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N
        int N = inf.readInt(4, 20000, "N");
        inf.readEoln();

        // Prepare DSU for clusters
        DSU dsu(N);
        int total_cmds = 0;
        int cnt_I = 0;

        // Read commands until 'O'
        while (true) {
            string cmd = inf.readToken("[EIO]", "command");
            if (cmd == "O") {
                // End of this test case
                inf.readEoln();
                break;
            }
            if (cmd == "E") {
                // Query: E I
                inf.readSpace();
                int I = inf.readInt(1, N, "E_I");
                inf.readEoln();
                total_cmds++;
            } else { // cmd == "I"
                // Instruction: I I J
                inf.readSpace();
                int I = inf.readInt(1, N, "I_I");
                inf.readSpace();
                int J = inf.readInt(1, N, "I_J");
                inf.readEoln();
                total_cmds++;
                cnt_I++;

                // Validate that I is a current center
                int rootI = dsu.find(I);
                ensuref(rootI == I,
                    "In test case %d, command #%d: node %d is not a center (root is %d)",
                    tc, total_cmds, I, rootI);

                // Validate that clusters are disjoint
                int rootJ = dsu.find(J);
                ensuref(rootJ != rootI,
                    "In test case %d, command #%d: clusters of %d and %d are already connected (root %d)",
                    tc, total_cmds, I, J, rootI);

                // Merge: new center is J's center (rootJ)
                dsu.unite_root_to(rootI, rootJ);
            }
        }

        // Validate command counts
        ensuref(total_cmds <= 200000,
                "In test case %d: total number of E and I commands (%d) exceeds 200000",
                tc, total_cmds);
        ensuref(cnt_I < N,
                "In test case %d: number of I commands (%d) must be less than N=%d",
                tc, cnt_I, N);
    }

    inf.readEof();
    return 0;
}

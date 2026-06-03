#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The primary BOJ Korean statement and official sample use one case
    // with 1 <= N <= 2000; the legacy English variant describes a T-case form.
    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    string traversal = inf.readToken("[01]{2,4000}", "traversal");
    inf.readEoln();
    ensuref((int)traversal.size() == 2 * n,
            "traversal length must be exactly 2N: length=%d, N=%d",
            (int)traversal.size(),
            n);

    int x = inf.readInt(1, 2 * n, "X");
    inf.readSpace();
    int y = inf.readInt(1, 2 * n, "Y");
    inf.readEoln();
    inf.readEof();

    vector<int> stack;
    vector<int> childCount(n, 0);
    int nodeCount = 0;

    for (int i = 0; i < 2 * n; ++i) {
        if (traversal[i] == '0') {
            ensuref(nodeCount < n,
                    "too many visited nodes before position %d",
                    i + 1);
            if (!stack.empty()) {
                ++childCount[stack.back()];
            }
            stack.push_back(nodeCount++);
        } else {
            ensuref(!stack.empty(),
                    "return at position %d has no matching visited node",
                    i + 1);
            int node = stack.back();
            stack.pop_back();
            ensuref(childCount[node] == 0 || childCount[node] >= 2,
                    "internal node %d has only one child",
                    node + 1);
        }
    }

    ensuref(nodeCount == n, "visited node count must be N: visited=%d, N=%d", nodeCount, n);
    ensuref(stack.empty(), "traversal has unreturned nodes");
    (void)x;
    (void)y;
}

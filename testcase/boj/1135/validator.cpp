#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of employees N: 1 ≤ N ≤ 50
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read parent array of size N
    vector<int> p(N);
    for (int i = 0; i < N; i++) {
        if (i > 0) {
            inf.readSpace();
        }
        char buf[20];
        sprintf(buf, "parent_%d", i);
        if (i == 0) {
            // 0-th employee must have parent = -1
            p[i] = inf.readInt(-1, -1, buf);
        } else {
            // For i >= 1, parent must be in [0, i-1]
            p[i] = inf.readInt(0, i-1, buf);
        }
    }
    inf.readEoln();

    // Validate hierarchy: every node must eventually reach 0
    for (int i = 0; i < N; i++) {
        int cur = i;
        // Follow parent chain until reaching 0
        while (cur != 0) {
            // p[cur] was already constrained in input range
            cur = p[cur];
        }
        // reached 0 successfully
    }

    inf.readEof();
    return 0;
}

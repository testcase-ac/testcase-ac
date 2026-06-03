#include "testlib.h"

#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(0, n, "m");
    inf.readSpace();
    long long k = inf.readLong(0LL, 5000000000LL, "k");
    inf.readEoln();

    vector<int> stones = inf.readInts(n, 1, 1000000, "s");
    inf.readEoln();

    set<int> closedEdges;
    for (int edgeIndex = 1; edgeIndex <= m; ++edgeIndex) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readEoln();

        int edgeId = -1;
        if (i == 1 && j == n) {
            edgeId = n;
        } else if (i == n && j == 1) {
            edgeId = n;
        } else if (i + 1 == j) {
            edgeId = i;
        } else if (j + 1 == i) {
            edgeId = j;
        }

        ensuref(edgeId != -1, "construction section %d is not between neighboring buildings: %d %d",
                edgeIndex, i, j);
        ensuref(closedEdges.insert(edgeId).second,
                "construction section %d duplicates circular edge %d", edgeIndex, edgeId);
    }

    inf.readEof();
}

#include "testlib.h"
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int Z = inf.readInt(1, 10, "Z");
    inf.readEoln();

    for (int test = 0; test < Z; ++test) {
        // Read A and B
        int A = inf.readInt(1, 100, "A");
        inf.readSpace();
        int B = inf.readInt(1, 100, "B");
        inf.readEoln();

        // Read a_i: costs of investments
        vector<int> a = inf.readInts(A, 1, 1000000, "a_i");
        inf.readEoln();

        // Read b_i: profits of benefits
        vector<int> b = inf.readInts(B, 1, 1000000, "b_i");
        inf.readEoln();

        // Read K
        int K = inf.readInt(1, A * B, "K");
        inf.readEoln();

        // Read K pairs (x_i, y_i)
        set<pair<int, int>> reqs;
        for (int i = 0; i < K; ++i) {
            int x = inf.readInt(1, A, "x_i");
            inf.readSpace();
            int y = inf.readInt(1, B, "y_i");
            inf.readEoln();

            ensuref(reqs.count({x, y}) == 0, "Duplicate requirement pair at index %d: (%d, %d)", i + 1, x, y);
            reqs.insert({x, y});
        }
    }

    inf.readEof();
}

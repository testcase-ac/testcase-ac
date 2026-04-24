#include "testlib.h"
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of islands and number of events
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    set<pair<int,int>> edges;
    for (int i = 1; i <= Q; i++) {
        // Read event type
        int type = inf.readInt(0, 2, "type");
        inf.readSpace();
        // Read X and Y
        int X = inf.readInt(0, N-1, "X");
        inf.readSpace();
        int Y = inf.readInt(0, N-1, "Y");
        ensuref(X != Y, "Event %d: X and Y must differ, got X=%d Y=%d", i, X, Y);

        pair<int,int> e = make_pair(min(X, Y), max(X, Y));

        if (type == 0) {
            // Insertion: also read V
            inf.readSpace();
            int V = inf.readInt(0, 9, "V");
            inf.readEoln();
            // Ensure no existing edge
            ensuref(!edges.count(e),
                    "Event %d: inserting edge (%d,%d) that already exists", i, X, Y);
            edges.insert(e);
        }
        else if (type == 1) {
            // Deletion
            inf.readEoln();
            // Ensure edge exists
            ensuref(edges.count(e),
                    "Event %d: deleting edge (%d,%d) that does not exist", i, X, Y);
            edges.erase(e);
        }
        else { // type == 2
            // Query
            inf.readEoln();
            // Nothing else to check for queries
        }
    }

    inf.readEof();
    return 0;
}

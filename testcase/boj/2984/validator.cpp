#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of trucks
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // To ensure all entry interchanges are distinct, and all exit interchanges are distinct
    set<int> entries, exits;
    entries.clear();
    exits.clear();

    for (int i = 0; i < N; i++) {
        // Read entry interchange number
        int en = inf.readInt(1, 1000000, "entry");
        inf.readSpace();
        // Read exit interchange number
        int ex = inf.readInt(1, 1000000, "exit");
        inf.readEoln();

        // Check for duplicate entries or exits
        ensuref(!entries.count(en),
                "Duplicate entry interchange %d at truck %d", en, i+1);
        ensuref(!exits.count(ex),
                "Duplicate exit interchange %d at truck %d", ex, i+1);

        entries.insert(en);
        exits.insert(ex);
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}

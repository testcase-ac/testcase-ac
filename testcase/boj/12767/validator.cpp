#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int k = inf.readInt(1, 20, "k");
    inf.readEoln();

    // Read each prototype line
    for (int i = 0; i < n; i++) {
        vector<int> vals = inf.readInts(k, 1, 1000000, "value");
        inf.readEoln();

        // Check distinctness within the line
        set<int> st(vals.begin(), vals.end());
        ensuref((int)st.size() == k,
                "Duplicate values found on line %d", i + 2);
        // (i+2) because line 1 is n, k; prototypes start at line 2
    }

    inf.readEof();
    return 0;
}

#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries N
    int N = inf.readInt(1, 118, "N");
    inf.readEoln();

    // Ensure that each atomic number is distinct
    set<int> seen;
    for (int i = 0; i < N; i++) {
        int a = inf.readInt(1, 118, "a");
        inf.readEoln();
        ensuref(!seen.count(a),
                "Duplicate atomic number %d at line %d", a, i + 2);
        seen.insert(a);
    }

    inf.readEof();
    return 0;
}

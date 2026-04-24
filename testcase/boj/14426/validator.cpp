#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read the set S of size N, ensure lowercase-only, length 1..500, and uniqueness
    set<string> seenS;
    for (int i = 0; i < N; i++) {
        // readToken ensures only a single token with no spaces
        string s = inf.readToken("[a-z]{1,500}", "S_i");
        inf.readEoln();
        bool inserted = seenS.insert(s).second;
        ensuref(inserted, "Duplicate string in S at index %d: %s", i, s.c_str());
    }

    // Read M query strings, ensure lowercase-only, length 1..500
    for (int j = 0; j < M; j++) {
        string t = inf.readToken("[a-z]{1,500}", "T_j");
        inf.readEoln();
        // No further constraints (duplicates allowed in queries)
    }

    // No extra data
    inf.readEof();
    return 0;
}

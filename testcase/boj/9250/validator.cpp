#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the set S of N distinct lowercase strings, length 1 to 100
    set<string> Sset;
    for (int i = 1; i <= N; i++) {
        string s = inf.readToken("[a-z]{1,100}", "S_element");
        inf.readEoln();
        // Ensure uniqueness since S is defined as a set
        ensuref(Sset.insert(s).second,
                "Duplicate string in S at index %d: \"%s\"", i, s.c_str());
    }

    // Read Q
    int Q = inf.readInt(1, 1000, "Q");
    inf.readEoln();

    // Read Q query strings, lowercase, length 1 to 10000
    for (int i = 1; i <= Q; i++) {
        string q = inf.readToken("[a-z]{1,10000}", "query");
        inf.readEoln();
        // No further validation needed for queries
    }

    inf.readEof();
    return 0;
}

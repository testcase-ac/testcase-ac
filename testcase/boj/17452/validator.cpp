#include "testlib.h"
#include <string>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of strings N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read N distinct strings S_i
    unordered_set<string> seen;
    seen.reserve((size_t)N * 2);

    for (int i = 0; i < N; i++) {
        // Each string must be 2 to 20 lowercase letters, no spaces
        string s = inf.readToken("[a-z]{2,20}", "S_i");
        inf.readEoln();

        // Check uniqueness
        ensuref(!seen.count(s),
                "Duplicate string detected at index %d: \"%s\"", i+1, s.c_str());
        seen.insert(s);
    }

    inf.readEof();
    return 0;
}

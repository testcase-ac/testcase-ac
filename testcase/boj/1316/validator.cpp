#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each word must be lowercase only, length 1 to 100, and no duplicates
    set<string> seen;
    for (int i = 0; i < N; i++) {
        string w = inf.readToken("[a-z]{1,100}", "word");
        inf.readEoln();
        // Check uniqueness
        ensuref(!seen.count(w),
                "Duplicate word detected at index %d: \"%s\"", i+1, w.c_str());
        seen.insert(w);
    }

    inf.readEof();
    return 0;
}

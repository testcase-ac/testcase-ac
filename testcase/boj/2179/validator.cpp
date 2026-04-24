#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words
    int N = inf.readInt(2, 20000, "N");
    inf.readEoln();

    set<string> seen;
    for (int i = 0; i < N; i++) {
        // Each word: lowercase letters only, length between 1 and 100
        string w = inf.readLine("[a-z]{1,100}", "word");
        // Check uniqueness
        ensuref(!seen.count(w),
                "Duplicate word at line %d: '%s'", i + 2, w.c_str());
        seen.insert(w);
    }

    inf.readEof();
    return 0;
}

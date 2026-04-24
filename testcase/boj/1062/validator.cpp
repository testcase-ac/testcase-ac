#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int K = inf.readInt(0, 26, "K");
    inf.readEoln();

    set<string> seen;
    for (int i = 0; i < N; i++) {
        // Each word: only lowercase letters, length between 8 and 15
        string w = inf.readLine("[a-z]{8,15}", "word");
        // Check prefix "anta"
        ensuref(w.size() >= 4, "word[%d] is too short to have prefix 'anta'", i);
        ensuref(w.substr(0,4) == "anta",
                "word[%d] does not start with 'anta': %s", i, w.c_str());
        // Check suffix "tica"
        ensuref(w.size() >= 4, "word[%d] is too short to have suffix 'tica'", i);
        ensuref(w.substr(w.size()-4,4) == "tica",
                "word[%d] does not end with 'tica': %s", i, w.c_str());
        // Check uniqueness
        ensuref(!seen.count(w),
                "Duplicate word at index %d: %s", i, w.c_str());
        seen.insert(w);
    }

    inf.readEof();
    return 0;
}

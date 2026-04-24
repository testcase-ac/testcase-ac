#include "testlib.h"
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words: must be between 1 and 100 inclusive.
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Read each word: must be 1 to 10 uppercase letters, no leading/trailing spaces.
    set<string> seen;
    for (int i = 0; i < n; i++) {
        // readLine with regex enforces exact match of the line to [A-Z]{1,10}
        string w = inf.readLine("[A-Z]{1,10}", "word");
        // Check for duplicate words: problem says all input words are distinct.
        bool inserted = seen.insert(w).second;
        ensuref(inserted,
                "Duplicate word detected at line %d: \"%s\"",
                i + 2, w.c_str());
    }

    // No extra content after the last line.
    inf.readEof();
    return 0;
}

#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 1 <= T < 100
    int T = inf.readInt(1, 99, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // Read the two words, uppercase only, length between 4 and 20
        string w1 = inf.readToken("[A-Z]{4,20}", "word1");
        inf.readSpace();
        string w2 = inf.readToken("[A-Z]{4,20}", "word2");
        inf.readEoln();

        // They must have the same length
        ensuref(w1.size() == w2.size(),
                "Test case %d: word lengths differ (%d vs %d)",
                tc, (int)w1.size(), (int)w2.size());
    }

    inf.readEof();
    return 0;
}

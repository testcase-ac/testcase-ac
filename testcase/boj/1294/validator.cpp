#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words N
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read each word, check constraints
    for (int i = 0; i < N; i++) {
        string w = inf.readToken("[A-Z]+", "word");
        // Check length constraints
        ensuref((int)w.length() <= 1000,
                "Length of word %d is %d, but must be at most 1000",
                i+1, (int)w.length());
        ensuref((int)w.length() >= 1,
                "Length of word %d is %d, but must be at least 1",
                i+1, (int)w.length());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

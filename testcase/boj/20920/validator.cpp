#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    // There must be at least one word of length >= M
    bool has_long = false;

    // Read N words
    for (int i = 0; i < N; i++) {
        // Each word: lowercase only, length 1..10
        string w = inf.readToken("[a-z]{1,10}", "word");
        inf.readEoln();
        if ((int)w.length() >= M) {
            has_long = true;
        }
    }

    ensuref(has_long,
        "There must be at least one word with length >= M");

    inf.readEof();
    return 0;
}

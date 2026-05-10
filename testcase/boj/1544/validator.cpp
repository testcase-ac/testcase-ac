#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        string word = inf.readToken("[a-z]{1,50}", "word");
        inf.readEoln();

        // Additional check: word must be only lowercase letters, length 1..50 (already checked by regex)
        ensuref((int)word.size() >= 1 && (int)word.size() <= 50, 
            "Word at line %d has invalid length: %d", i+2, (int)word.size());
        for (char c : word) {
            ensuref('a' <= c && c <= 'z', 
                "Word at line %d contains invalid character: '%c'", i+2, c);
        }
    }

    inf.readEof();
}

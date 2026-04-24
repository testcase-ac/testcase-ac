#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of dictionary words
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Sum of lengths of all dictionary words
    long long sumLen = 0;

    // Read each dictionary word
    for (int i = 0; i < N; i++) {
        // Each word: non-empty lowercase, length up to 300, no spaces
        string w = inf.readToken("[a-z]{1,300}", "word");
        inf.readEoln();
        sumLen += (int)w.size();
        ensuref(sumLen <= 1000000,
                "Sum of lengths of dictionary words exceeds 1e6 (currently %lld)", sumLen);
    }

    // Read the target string: non-empty lowercase, length up to 200000
    string target = inf.readToken("[a-z]{1,200000}", "target");
    inf.readEoln();

    // No further global constraints (answer can be zero or any modulo), just EOF
    inf.readEof();
    return 0;
}

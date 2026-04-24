#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the length of the string
    int L = inf.readInt(1, 200000, "L");
    inf.readEoln();

    // Read the string of lowercase letters
    // We accept at least one lowercase letter, then check exact length
    string s = inf.readLine("[a-z]+", "s");
    ensuref((int)s.size() == L,
            "String length mismatch: expected %d, got %d", L, (int)s.size());

    // No extra data
    inf.readEof();
    return 0;
}

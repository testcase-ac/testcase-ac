#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single word: only uppercase and lowercase letters, length between 1 and 100
    string s = inf.readToken("[a-zA-Z]+", "s");
    int n = (int)s.size();
    ensuref(n >= 1, "The word must be non-empty");
    ensuref(n <= 100, "The word length must not exceed 100, but got %d", n);

    inf.readEoln();
    inf.readEof();
    return 0;
}

#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L
    int L = inf.readInt(1, 200000, "L");
    inf.readEoln();

    // Read the string of length L, consisting only of lowercase letters
    // We allow any length from 1 to 200000 in the regex, then enforce exact L below
    string s = inf.readLine("[a-z]{1,200000}", "s");
    ensuref((int)s.size() == L,
            "Length of string s is %d but expected %d", (int)s.size(), L);

    inf.readEof();
    return 0;
}

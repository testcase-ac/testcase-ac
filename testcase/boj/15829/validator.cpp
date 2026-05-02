#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L
    int L = inf.readInt(1, 50, "L");
    inf.readEoln();

    // Read string of lowercase letters
    // We allow lengths up to 50 in regex, but enforce exact length == L
    string s = inf.readToken("[a-z]{1,50}", "s");
    ensuref((int)s.size() == L,
            "Length of string s is %d but expected %d", (int)s.size(), L);
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}

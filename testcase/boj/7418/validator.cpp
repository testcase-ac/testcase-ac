#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement says the input has at most 100 brackets and defines
    // the empty sequence, so a single empty line is accepted as length 0.
    string s = inf.readLine("[^]{0,100}", "s");
    for (int i = 0; i < (int)s.size(); ++i) {
        ensuref(s[i] == '(' || s[i] == ')' || s[i] == '[' || s[i] == ']',
                "invalid bracket character at position %d: ASCII %d",
                i + 1, (int)(unsigned char)s[i]);
    }

    inf.readEof();
}

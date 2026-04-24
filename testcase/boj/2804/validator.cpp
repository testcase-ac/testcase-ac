#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read words A and B: uppercase only, length 1 to 30
    string A = inf.readToken("[A-Z]{1,30}", "A");
    inf.readSpace();
    string B = inf.readToken("[A-Z]{1,30}", "B");
    inf.readEoln();

    // Check that there's at least one common character
    set<char> chars_in_A;
    for (char c : A) {
        chars_in_A.insert(c);
    }
    bool has_common = false;
    for (char c : B) {
        if (chars_in_A.count(c)) {
            has_common = true;
            break;
        }
    }
    ensuref(has_common,
            "Words A and B must share at least one common uppercase letter; A=\"%s\", B=\"%s\"",
            A.c_str(), B.c_str());

    inf.readEof();
    return 0;
}

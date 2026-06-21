#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{1,499999}", "s");
    inf.readEoln();
    ensuref(!equal(s.begin(), s.begin() + s.size() / 2, s.rbegin()),
            "s must not be a palindrome");

    inf.readEof();
}

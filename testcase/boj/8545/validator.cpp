#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // One and only line: a three-letter word.
    // The statement doesn't restrict alphabet type, so accept any non-whitespace chars.
    string s = inf.readToken("[^ \t\r\n]{3}", "word");
    inf.readEoln();

    // Ensure it's exactly length 3 (regex already enforces, but double-check explicitly)
    ensuref((int)s.size() == 3, "word must be exactly 3 characters long");

    inf.readEof();
}

#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[01]{2,300}", "S");
    inf.readEoln();
    inf.readEof();

    ensuref(2 <= (int)s.size() && (int)s.size() <= 300,
            "S length must be between 2 and 300, found %d", (int)s.size());
}

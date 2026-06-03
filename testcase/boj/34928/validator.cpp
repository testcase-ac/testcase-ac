#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 100000, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{4,100000}", "S");
    inf.readEoln();

    ensuref((int)s.size() == n, "S length is %d, expected %d", (int)s.size(), n);
    ensuref(s.find('P') != string::npos, "S must contain P");
    ensuref(s.find('A') != string::npos, "S must contain A");
    ensuref(s.find('U') != string::npos, "S must contain U");
    ensuref(s.find('L') != string::npos, "S must contain L");

    inf.readEof();
}

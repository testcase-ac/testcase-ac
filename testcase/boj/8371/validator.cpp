#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    string pattern = "[A-Za-z]{" + to_string(n) + "}";
    inf.readToken(pattern, "original");
    inf.readEoln();
    inf.readToken(pattern, "rewritten");
    inf.readEoln();

    inf.readEof();
}

#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    string pattern = "[01]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(pattern, "row");
        inf.readEoln();
    }

    inf.readEof();
}

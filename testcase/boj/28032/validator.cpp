#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 18, "C");
    inf.readSpace();
    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    string pattern = "[GH]{" + to_string(c) + "," + to_string(c) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(pattern, "team");
        inf.readEoln();
    }

    inf.readEof();
}

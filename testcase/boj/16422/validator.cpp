#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int s = inf.readInt(1, min(n, 100), "s");
    inf.readEoln();

    string pattern = "[CD]{" + to_string(n) + "," + to_string(n) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(pattern, "row");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        string s = inf.readToken("[()\\[\\]{}*]{1,500}", "s");
        inf.readEoln();
    }

    inf.readEof();
}

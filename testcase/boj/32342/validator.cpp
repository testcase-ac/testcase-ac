#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 100, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);
        string s = inf.readLine("[WO]{1,1000}", "S");
        ensuref(!s.empty(), "S must be non-empty");
    }

    inf.readEof();
}

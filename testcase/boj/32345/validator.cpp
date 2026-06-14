#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalLength = 0;
    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        string s = inf.readToken("[a-z]{1,300000}", "S");
        inf.readEoln();

        totalLength += static_cast<long long>(s.size());
        ensuref(totalLength <= 1000000, "sum of |S| exceeds 1000000");
    }

    inf.readEof();
}

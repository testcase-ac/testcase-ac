#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = inf.readInt(1, 500000, "T");
    inf.readEoln();

    long long totalA = 0;
    long long totalB = 0;
    for (int test = 1; test <= testCount; ++test) {
        setTestCase(test);
        string a = inf.readToken("[()]{1,500000}", "A");
        inf.readSpace();
        string b = inf.readToken("[()]{1,500000}", "B");
        inf.readEoln();

        totalA += a.size();
        totalB += b.size();
        ensuref(totalA <= 500000, "sum of |A| exceeds 500000");
        ensuref(totalB <= 500000, "sum of |B| exceeds 500000");
    }

    inf.readEof();
}

#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 20000, "z");
    inf.readEoln();

    long long totalDigits = 0;
    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        string n = inf.readToken("[1-9][0-9]{0,99999}", "n");
        totalDigits += static_cast<long long>(n.size());
        ensuref(totalDigits <= 3000000LL,
                "total number of digits exceeds 3000000 after test case %d", tc);
        inf.readEoln();
    }

    inf.readEof();
}

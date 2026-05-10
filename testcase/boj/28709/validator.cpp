#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    long long totalLen = 0;
    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        string s = inf.readToken("[()\\?\\*]{1,500000}", "S");
        inf.readEoln();

        int n = (int)s.size();
        totalLen += n;
        ensuref(totalLen <= 500000,
                "Sum of lengths of all strings exceeds 500000 (currently %lld)", totalLen);
    }

    inf.readEof();
}

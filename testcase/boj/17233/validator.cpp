#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100;
    const int MAX_PATTERN_LENGTH = 10000;
    const int MAX_S_LENGTH = 500000;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<string> patterns;
    patterns.reserve(n);
    for (int i = 1; i <= n; ++i) {
        int length = inf.readInt(1, MAX_PATTERN_LENGTH, "P_length");
        inf.readSpace();
        string pattern = inf.readToken("[a-z]+", "P");
        inf.readEoln();

        ensuref((int)pattern.size() == length,
                "P_%d length is %d, expected %d",
                i,
                (int)pattern.size(),
                length);
        patterns.push_back(pattern);
    }

    int sLength = inf.readInt(1, MAX_S_LENGTH, "S_length");
    inf.readSpace();
    string s = inf.readToken("[a-z]+", "S");
    inf.readEoln();

    ensuref((int)s.size() == sLength,
            "S length is %d, expected %d",
            (int)s.size(),
            sLength);

    for (int i = 0; i < n; ++i) {
        ensuref(s.find(patterns[i]) != string::npos,
                "P_%d is not a substring of S",
                i + 1);
    }

    inf.readEof();
    return 0;
}

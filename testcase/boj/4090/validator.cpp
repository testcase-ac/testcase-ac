#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_X = 10;
    const int MAX_X = 1000000;
    const int MAX_CASES = 100000;

    int case_cnt = 0;
    while (true) {
        // Read the line as a token (to check for leading zeros)
        string token = inf.readToken("[0-9]+", "X");
        // Check for leading zeros (except for "0" itself)
        ensuref(!(token.size() > 1 && token[0] == '0'), "Leading zeros are not allowed in X: '%s'", token.c_str());

        // Convert to integer
        long long X = 0;
        for (char c : token) X = X * 10 + (c - '0');

        // After token, must be EOLN
        inf.readEoln();

        // Check for end marker
        if (X == 0) {
            break;
        }

        // Check range
        ensuref(MIN_X <= X && X <= MAX_X, "X=%lld is out of range [%d, %d]", X, MIN_X, MAX_X);

        ++case_cnt;
        ensuref(case_cnt <= MAX_CASES, "Too many test cases: %d (max %d)", case_cnt, MAX_CASES);
    }

    inf.readEof();
}

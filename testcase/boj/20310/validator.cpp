#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S
    string S = inf.readToken("[01]{2,500}", "S");
    inf.readEoln();

    int n = S.size();
    ensuref(n >= 2 && n <= 500, "Length of S must be between 2 and 500, got %d", n);

    int cnt0 = 0, cnt1 = 0;
    for (int i = 0; i < n; ++i) {
        ensuref(S[i] == '0' || S[i] == '1', "S[%d] is not 0 or 1: '%c'", i, S[i]);
        if (S[i] == '0') cnt0++;
        else cnt1++;
    }

    ensuref(cnt0 % 2 == 0, "Number of 0's (%d) is not even", cnt0);
    ensuref(cnt1 % 2 == 0, "Number of 1's (%d) is not even", cnt1);

    inf.readEof();
}

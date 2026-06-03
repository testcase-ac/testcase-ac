#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    int answerCount = 0;
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[A-Z]{1,100}", "name");
        inf.readEoln();
        if (name.find('S') != string::npos) {
            ++answerCount;
        }
    }

    ensuref(answerCount == 1, "expected exactly one name containing S, found %d", answerCount);

    inf.readEof();
}

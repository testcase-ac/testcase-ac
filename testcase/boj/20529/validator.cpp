#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    int totalN = 0;
    const string mbtiPattern =
        "ISTJ|ISFJ|INFJ|INTJ|ISTP|ISFP|INFP|INTP|"
        "ESTP|ESFP|ENFP|ENTP|ESTJ|ESFJ|ENFJ|ENTJ";

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 100000, "N");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= 100000, "sum of N exceeds 100000 after testcase %d", tc);

        for (int i = 0; i < n; ++i) {
            inf.readToken(mbtiPattern, "MBTI");
            if (i + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}

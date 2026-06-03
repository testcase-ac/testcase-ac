#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string mbti = inf.readToken("[A-Z]{4}", "mbti");
    inf.readEoln();

    ensuref(mbti[0] == 'E' || mbti[0] == 'I',
            "first MBTI indicator must be E or I, got %c", mbti[0]);
    ensuref(mbti[1] == 'S' || mbti[1] == 'N',
            "second MBTI indicator must be S or N, got %c", mbti[1]);
    ensuref(mbti[2] == 'T' || mbti[2] == 'F',
            "third MBTI indicator must be T or F, got %c", mbti[2]);
    ensuref(mbti[3] == 'J' || mbti[3] == 'P',
            "fourth MBTI indicator must be J or P, got %c", mbti[3]);

    inf.readEof();
}

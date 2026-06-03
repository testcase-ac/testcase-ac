#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const set<string> validTypes = {
        "INFP", "ENFP", "ISFP", "ESFP",
        "INTP", "ENTP", "ISTP", "ESTP",
        "INFJ", "ENFJ", "ISFJ", "ESFJ",
        "INTJ", "ENTJ", "ISTJ", "ESTJ",
    };

    auto readMbti = [&](const char* name) {
        string mbti = inf.readToken("[A-Z]{4}", name);
        ensuref(validTypes.count(mbti), "%s is not a valid MBTI type: %s", name, mbti.c_str());
        inf.readEoln();
    };

    readMbti("jinho");

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        readMbti("friend_i");
    }

    inf.readEof();
}

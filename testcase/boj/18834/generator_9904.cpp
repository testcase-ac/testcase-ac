#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string genLetters(int len, bool onlyD = false) {
    string s;
    s.reserve(len);
    const string ops = "LRUD";
    for (int i = 0; i < len; i++) {
        if (onlyD) s.push_back('D');
        else s.push_back(ops[rnd.next(0, 3)]);
    }
    return s;
}

// Generate expression with *non-nested* groups of form (LRUD...)n
string genWithGroups(int maxSegments, int letterMin, int letterMax, int nMax) {
    int segments = rnd.next(1, maxSegments);
    string res;
    const string ops = "LRUD";

    for (int i = 0; i < segments; i++) {
        bool makeGroup = rnd.next(0, 1) == 1;
        int len = rnd.next(letterMin, letterMax);

        string letters;
        letters.reserve(len);
        for (int j = 0; j < len; j++) {
            letters.push_back(ops[rnd.next(0, 3)]);
        }

        if (makeGroup) {
            int rep = rnd.next(1, nMax);
            res.push_back('(');
            res += letters;
            res.push_back(')');
            res += to_string(rep);
        } else {
            res += letters;
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Use only known valid starting configurations from samples
    vector<pair<string, string>> starts = {
        {"하이퍼", "구데기컵"},
        {"QR", "퍼즐헌트"}
    };
    auto st = rnd.any(starts);
    println(st.first, st.second);

    // Choose mode for command generation
    int mode = rnd.next(0, 3); // 0,1,2,3

    string cmd;
    if (mode == 0) {
        // Subtask 1 style: only D
        int len = (rnd.next(0, 1) == 0) ? rnd.next(1, 10) : rnd.next(11, 40);
        cmd = genLetters(len, true);
    } else if (mode == 1) {
        // Subtask 2 style: LRUD only, no parentheses
        int len = (rnd.next(0, 1) == 0) ? rnd.next(1, 20) : rnd.next(21, 80);
        cmd = genLetters(len, false);
    } else if (mode == 2) {
        // Subtask 3 style: with simple non-nested groups, n <= 3
        cmd = genWithGroups(5, 1, 3, 3);
    } else {
        // Full style: non-nested groups, large n allowed but overall string small
        cmd = genWithGroups(8, 1, 4, 999999999); // n < 1e9
    }

    // Safety: ensure non-empty
    if (cmd.empty()) cmd = "D";

    println(cmd);

    return 0;
}

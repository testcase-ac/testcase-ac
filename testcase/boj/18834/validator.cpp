#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<string> names = {
        "구데기컵", "하이퍼", "0초제출", "알파고", "박승원", "애이불비",
        "배중률교", "미니앨범", "주령구", "QR", "퍼즐헌트", "데쿼리",
        "연속합", "대결!"
    };
    map<string, int> id;
    for (int i = 0; i < (int)names.size(); ++i) {
        id[names[i]] = i;
    }

    const vector<vector<int>> around = {
        {12, 1, 13, 9},
        {2, 5, 0},
        {3, 4, 1, 12},
        {7, 2, 10},
        {2, 7, 5},
        {1, 4, 8, 13},
        {9, 13, 8, 11},
        {11, 8, 4, 3},
        {5, 7, 6},
        {10, 0, 6},
        {3, 12, 9, 11},
        {10, 6, 7},
        {2, 0, 10},
        {0, 5, 6}
    };

    string bottom = inf.readToken("[^ \t\r\n]+", "bottom_face");
    inf.readSpace();
    string down = inf.readToken("[^ \t\r\n]+", "down_face");
    inf.readEoln();

    ensuref(id.count(bottom), "unknown bottom face: %s", bottom.c_str());
    ensuref(id.count(down), "unknown down face: %s", down.c_str());
    int bottomId = id[bottom];
    int downId = id[down];
    ensuref(find(around[bottomId].begin(), around[bottomId].end(), downId) !=
                around[bottomId].end(),
            "down face %s is not adjacent to bottom face %s",
            down.c_str(), bottom.c_str());

    string s = inf.readToken("[LRUD()0-9]+", "commands");
    inf.readEoln();
    ensuref(1 <= (int)s.size() && (int)s.size() <= 200000,
            "command string length must be in [1, 200000], got %d",
            (int)s.size());

    vector<bool> hasContent;
    for (int i = 0; i < (int)s.size();) {
        char c = s[i];
        if (c == 'L' || c == 'R' || c == 'U' || c == 'D') {
            if (!hasContent.empty()) {
                hasContent.back() = true;
            }
            ++i;
        } else if (c == '(') {
            hasContent.push_back(false);
            ++i;
        } else if (c == ')') {
            ensuref(!hasContent.empty(), "unmatched ')' at position %d", i + 1);
            ensuref(hasContent.back(), "empty group ending at position %d", i + 1);
            hasContent.pop_back();
            if (!hasContent.empty()) {
                hasContent.back() = true;
            }
            ++i;

            ensuref(i < (int)s.size() && isdigit((unsigned char)s[i]),
                    "missing multiplier after ')' at position %d", i);
            int start = i;
            long long value = 0;
            while (i < (int)s.size() && isdigit((unsigned char)s[i])) {
                value = value * 10 + (s[i] - '0');
                ensuref(value < 1000000000LL,
                        "multiplier starting at position %d must be less than 1e9",
                        start + 1);
                ++i;
            }
            ensuref(s[start] != '0',
                    "multiplier starting at position %d must not have leading zero",
                    start + 1);
            ensuref(value >= 1,
                    "multiplier starting at position %d must be at least 1",
                    start + 1);
        } else {
            ensuref(false, "unexpected digit at position %d", i + 1);
        }
    }

    ensuref(hasContent.empty(), "unmatched '(' in command string");
    inf.readEof();
}

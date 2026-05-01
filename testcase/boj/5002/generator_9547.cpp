#include "testlib.h"
using namespace std;

string genAlternating(int len) {
    string s;
    s.reserve(len);
    char c = rnd.any(string("MW"));
    for (int i = 0; i < len; i++) {
        s.push_back(c);
        c = (c == 'M' ? 'W' : 'M');
    }
    return s;
}

string genBlocks(int totalLen) {
    string s;
    s.reserve(totalLen);
    char cur = rnd.any(string("MW"));
    while ((int)s.size() < totalLen) {
        int rem = totalLen - (int)s.size();
        int blockLen = rnd.next(1, min(7, rem));
        s.append(blockLen, cur);
        cur = (cur == 'M' ? 'W' : 'M');
    }
    return s;
}

string genMajorityMinority(int maxLen) {
    int totalLen = rnd.next(8, maxLen);
    int majorityLen = rnd.next(totalLen / 2 + 1, totalLen - 1);
    int minorityLen = totalLen - majorityLen;

    char maj = rnd.any(string("MW"));
    char mino = (maj == 'M' ? 'W' : 'M');

    string s;
    s.reserve(totalLen);

    if (rnd.next(0, 1) == 0) {
        s.append(majorityLen, maj);
        s.append(minorityLen, mino);
    } else {
        s.append(minorityLen, mino);
        s.append(majorityLen, maj);
    }

    return s;
}

string genBalancedPairs(int maxLen) {
    int pairs = rnd.next(2, maxLen / 2);
    int extra = rnd.next(0, max(0, maxLen - 2 * pairs));
    int totalLen = 2 * pairs + extra;

    string s;
    s.reserve(totalLen);
    for (int i = 0; i < pairs; i++) {
        if (rnd.next(0, 1) == 0)
            s += "MW";
        else
            s += "WM";
    }
    for (int i = 0; i < extra; i++) {
        s.push_back(rnd.any(string("MW")));
    }
    return s;
}

string genRandomString(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; i++)
        s.push_back(rnd.any(string("MW")));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(1, 7);
    int X;
    string s;

    switch (type) {
        case 1: { // Fully random, small
            int len = rnd.next(1, 30);
            X = rnd.next(0, min(10, len));
            s = genRandomString(len);
            break;
        }
        case 2: { // Alternating pattern
            int len = rnd.next(5, 40);
            X = rnd.next(0, 3);
            s = genAlternating(len);
            break;
        }
        case 3: { // Block pattern
            int len = rnd.next(10, 35);
            X = rnd.next(1, min(8, len));
            s = genBlocks(len);
            break;
        }
        case 4: { // Strong majority followed by minority
            int lenLimit = 40;
            s = genMajorityMinority(lenLimit);
            int len = (int)s.size();
            X = rnd.next(1, min(10, max(2, len / 3)));
            break;
        }
        case 5: { // Balanced pairs, small X
            int lenLimit = 40;
            s = genBalancedPairs(lenLimit);
            X = rnd.next(0, 3);
            break;
        }
        case 6: { // X = 0 edge cases
            int len = rnd.next(1, 20);
            X = 0;
            s = genRandomString(len);
            break;
        }
        case 7: { // Hand-crafted / sample-like cases
            vector<pair<int,string>> cases = {
                {1, "MWWMWMMWM"},            // sample 1
                {2, "WMMMMWWMMMWWMW"},       // sample 2
                {1, "MMMWWWWMMM"},           // long runs
                {0, "MWMWMWMW"},             // perfectly alternating, X=0
                {1, "WWMMMWMMW"},            // mixed
                {2, "MMMMMWWWWWM"},          // heavy majority then switch
            };
            auto cs = rnd.any(cases);
            X = cs.first;
            s = cs.second;
            break;
        }
    }

    // Ensure constraints
    if (X >= 100) X = 99;
    if ((int)s.size() > 100) s.resize(100);
    if (s.empty()) {
        s = "M";
        if (X < 0) X = 0;
    }

    println(X);
    println(s);

    return 0;
}

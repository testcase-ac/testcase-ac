#include "testlib.h"
#include <string>
#include <vector>
#include <cassert>
using namespace std;

// map single Roman character to its value
int romanCharVal(char c) {
    switch(c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

// convert an integer in [1,3999] to its canonical Roman numeral
string toRoman(int x) {
    static const vector<pair<int,const char*>> conv = {
        {1000,"M"},{900,"CM"},{500,"D"},{400,"CD"},
        {100,"C"},{90,"XC"},{50,"L"},{40,"XL"},
        {10,"X"},{9,"IX"},{5,"V"},{4,"IV"},{1,"I"}
    };
    string s;
    for (auto &p : conv) {
        while (x >= p.first) {
            s += p.second;
            x -= p.first;
        }
    }
    return s;
}

// parse a Roman numeral s, enforcing allowed subtractive pairs and basic repetition rules
// returns its integer value, or aborts via ensuref on invalid
int parseRoman(const string &s, const string &name) {
    int n = s.size();
    ensuref(n > 0, "%s: empty string", name.c_str());
    // counters for V,L,D usage
    int cntV = 0, cntL = 0, cntD = 0;
    // subtractive usage flags
    bool usedIV = false, usedIX = false, usedXL = false,
         usedXC = false, usedCD = false, usedCM = false;
    // consecutive counts for I,X,C,M
    char lastChar = 0;
    int consec = 0;
    int i = 0;
    int value = 0;
    while (i < n) {
        char c = s[i];
        int v = romanCharVal(c);
        ensuref(v > 0, "%s: invalid character '%c' at position %d", name.c_str(), c, i);
        // repetition tracking
        if (c == lastChar) {
            consec++;
        } else {
            lastChar = c;
            consec = 1;
        }
        // V, L, D cannot repeat at all
        if (c == 'V') { cntV++; ensuref(cntV <= 1, "%s: 'V' used more than once", name.c_str()); }
        if (c == 'L') { cntL++; ensuref(cntL <= 1, "%s: 'L' used more than once", name.c_str()); }
        if (c == 'D') { cntD++; ensuref(cntD <= 1, "%s: 'D' used more than once", name.c_str()); }
        // I,X,C,M can repeat at most 3 times in a row
        if (c=='I' || c=='X' || c=='C' || c=='M') {
            ensuref(consec <= 3, "%s: '%c' repeated more than 3 times in a row", name.c_str(), c);
        }
        // lookahead for subtractive
        if (i+1 < n) {
            char c2 = s[i+1];
            int v2 = romanCharVal(c2);
            if (v < v2) {
                // it's subtractive; check allowed pairs
                if (c=='I' && c2=='V') {
                    ensuref(!usedIV, "%s: 'IV' used more than once", name.c_str());
                    usedIV = true;
                    value += 4;
                } else if (c=='I' && c2=='X') {
                    ensuref(!usedIX, "%s: 'IX' used more than once", name.c_str());
                    usedIX = true;
                    value += 9;
                } else if (c=='X' && c2=='L') {
                    ensuref(!usedXL, "%s: 'XL' used more than once", name.c_str());
                    usedXL = true;
                    value += 40;
                } else if (c=='X' && c2=='C') {
                    ensuref(!usedXC, "%s: 'XC' used more than once", name.c_str());
                    usedXC = true;
                    value += 90;
                } else if (c=='C' && c2=='D') {
                    ensuref(!usedCD, "%s: 'CD' used more than once", name.c_str());
                    usedCD = true;
                    value += 400;
                } else if (c=='C' && c2=='M') {
                    ensuref(!usedCM, "%s: 'CM' used more than once", name.c_str());
                    usedCM = true;
                    value += 900;
                } else {
                    ensuref(false, "%s: invalid subtractive pair '%c%c' at pos %d", name.c_str(), c, c2, i);
                }
                // some pairs cannot coexist
                ensuref(!(usedIV && usedIX), "%s: both 'IV' and 'IX' used", name.c_str());
                ensuref(!(usedXL && usedXC), "%s: both 'XL' and 'XC' used", name.c_str());
                ensuref(!(usedCD && usedCM), "%s: both 'CD' and 'CM' used", name.c_str());
                // consume both
                i += 2;
                // reset repetition after subtractive
                lastChar = 0; consec = 0;
                continue;
            }
        }
        // non-subtractive case
        value += v;
        i++;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // read two Roman numerals, one per line
    string s1 = inf.readLine("[IVXLCDM]+", "roman1");
    string s2 = inf.readLine("[IVXLCDM]+", "roman2");

    int v1 = parseRoman(s1, "roman1");
    int v2 = parseRoman(s2, "roman2");

    // each input ≤ 2000
    ensuref(v1 <= 2000, "roman1 value %d exceeds 2000", v1);
    ensuref(v2 <= 2000, "roman2 value %d exceeds 2000", v2);

    int sum = v1 + v2;
    ensuref(sum < 4000, "sum %d is not less than 4000", sum);

    // check minimal (canonical) form
    string c1 = toRoman(v1);
    string c2 = toRoman(v2);
    ensuref(s1 == c1, "roman1 '%s' is not minimal canonical '%s'", s1.c_str(), c1.c_str());
    ensuref(s2 == c2, "roman2 '%s' is not minimal canonical '%s'", s2.c_str(), c2.c_str());

    inf.readEof();
    return 0;
}

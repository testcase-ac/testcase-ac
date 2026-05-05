#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Convert a block of Ms (with flag hasK meaning form 5*10^N) to its decimal string
string mkDigit(int mCount, bool hasK) {
    // value is either 10^N or 5*10^N
    int N;
    if (hasK) {
        // 5 * 10^N with representation M^N K
        N = mCount;
        // produce '5' followed by N zeros
        string res = "5";
        res.append(N, '0');
        return res;
    } else {
        // 10^N with representation M^(N+1)
        // So N = mCount - 1, and value is 1 followed by N zeros
        N = mCount - 1;
        string res = "1";
        res.append(N, '0');
        return res;
    }
}

// Add decimal strings a + b (non-negative, no leading zeros unless "0")
string addStr(const string &a, const string &b) {
    string res;
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int x = carry;
        if (i >= 0) x += a[i--] - '0';
        if (j >= 0) x += b[j--] - '0';
        res.push_back(char('0' + (x % 10)));
        carry = x / 10;
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

// Compare decimal strings without leading zeros
int cmpStr(const string &a, const string &b) {
    if (a.size() != b.size()) return (a.size() < b.size()) ? -1 : 1;
    if (a == b) return 0;
    return (a < b) ? -1 : 1;
}

// Multiply decimal string by 10^k (append k zeros)
string mulPow10(const string &a, int k) {
    if (a == "0") return "0";
    string res = a;
    res.append(k, '0');
    return res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[MK]{1,3000}", "s");
    // length between 1 and 3000 per statement; they say "does not exceed 3000", minimum is "one or more"
    ensuref(!s.empty(), "Input string must be non-empty");

    // No extra lines
    inf.readEof();

    int n = (int)s.size();

    // Compute maximal decimal value as in known greedy:
    // Group consecutive Ms ending with last K or end.
    string maxVal = "0";
    int cntM = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'M') {
            cntM++;
        } else { // 'K'
            // produce 5 * 10^(cntM+? ) logic for maximum:
            // known from problem editorial: for max, for a block of (M...M)K, make '5' then (cntM+1) zeros
            string digit = "5";
            digit.append(cntM + 1, '0');
            maxVal = addStr(maxVal, digit);
            cntM = 0;
        }
    }
    // remaining Ms: each becomes '1' then zeros in descending powers, for max
    // So for remaining cntM Ms, we create numbers 10^(cntM-1), 10^(cntM-2), ..., 10^0
    for (int i = 0; i < cntM; i++) {
        int pow = cntM - 1 - i;
        string digit = "1";
        digit.append(pow, '0');
        maxVal = addStr(maxVal, digit);
    }

    // Compute minimal decimal value:
    string minVal = "0";
    cntM = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'M') {
            cntM++;
        } else { // 'K'
            // block of Ms before K: for min, all those Ms except the last one become separate '1's
            // and last M with this K becomes '5' * 10^(cntM-1)
            if (cntM > 0) {
                // one digit: 10^(cntM) /2? Actually minimal rule from editorial:
                // Make a single 10^(cntM) number for Ms (as many as possible) except
                // at K, we make smallest 10^(cntM-1)*5.
                string digit = "5";
                digit.append(cntM - 1, '0');
                minVal = addStr(minVal, digit);
                cntM = 0;
            }
            // single K with no preceding M -> it's just 5
            if (i > 0 && s[i-1] == 'M') {
                // already handled in block
            } else if (cntM == 0) {
                // no preceding M: just '5'
                minVal = addStr(minVal, "5");
            }
        }
    }
    // remaining Ms at end: all grouped as one smallest: 10^(cntM-1)
    if (cntM > 0) {
        string digit = "1";
        digit.append(cntM - 1, '0');
        minVal = addStr(minVal, digit);
    }

    // Just basic sanity: maxVal >= minVal
    ensuref(cmpStr(maxVal, minVal) >= 0,
            "Internal sanity: maximal value must be >= minimal value, got max=%s min=%s",
            maxVal.c_str(), minVal.c_str());

    return 0;
}

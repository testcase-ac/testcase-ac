#include "testlib.h"
using namespace std;

string squareString(const string &s) {
    int n = (int)s.size();
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = s[n - 1 - i] - '0'; // reversed digits

    vector<int> res(2 * n + 2, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i + j] += a[i] * a[j];
        }
    }

    int carry = 0;
    for (int k = 0; k < (int)res.size(); k++) {
        int cur = res[k] + carry;
        res[k] = cur % 10;
        carry = cur / 10;
    }
    while (carry > 0) {
        res.push_back(carry % 10);
        carry /= 10;
    }

    while (res.size() > 1 && res.back() == 0)
        res.pop_back();

    string out;
    out.reserve(res.size());
    for (int i = (int)res.size() - 1; i >= 0; i--)
        out.push_back(char('0' + res[i]));
    return out;
}

string randomDigits(int len, bool allowLeadingZero = false) {
    string s(len, '0');
    for (int i = 0; i < len; i++) {
        if (i == 0 && !allowLeadingZero) {
            s[i] = char('1' + rnd.next(0, 8)); // 1..9
        } else {
            s[i] = char('0' + rnd.next(0, 9)); // 0..9
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string N;
    int scenario = rnd.next(1, 9);

    switch (scenario) {
        case 1: {
            // Very small square (easily checkable)
            int x = rnd.next(1, 1000);
            unsigned long long sq = 1ULL * x * x;
            N = to_string(sq);
            break;
        }
        case 2: {
            // Up to near 64-bit limit, but still within it
            unsigned int x = rnd.next(1U, 3000000000U); // <= 3e9
            unsigned long long sq = 1ULL * x * x;
            N = to_string(sq);
            break;
        }
        case 3: {
            // Just beyond 64-bit range: 11-20 digit square root
            int lenS = rnd.next(11, 20);
            string S = randomDigits(lenS, false);
            N = squareString(S);
            break;
        }
        case 4: {
            // Perfect powers of 10: (10^k)^2 = 1 followed by 2k zeros
            int k = rnd.next(1, 200); // N length = 2k+1 <= 401
            N = "1" + string(2 * k, '0');
            break;
        }
        case 5: {
            // Large random square root, 50-200 digits
            int lenS = rnd.next(50, 200);
            string S = randomDigits(lenS, false);
            N = squareString(S);
            break;
        }
        case 6: {
            // Square root of all 9s, 5-200 digits
            int lenS = rnd.next(5, 200);
            string S(lenS, '9');
            N = squareString(S);
            break;
        }
        case 7: {
            // Patterned square root: "1234567890..." truncated
            int lenS = rnd.next(10, 200);
            string pattern = "1234567890";
            string S;
            S.reserve(lenS);
            for (int i = 0; i < lenS; i++)
                S.push_back(pattern[i % (int)pattern.size()]);
            if (S[0] == '0') S[0] = '1';
            N = squareString(S);
            break;
        }
        case 8: {
            // Mixed-size random big square root, 1-248 digits
            // Bias towards larger sizes
            int lenS;
            int t = rnd.next(0, 2);
            if (t == 0) lenS = rnd.next(1, 5);
            else if (t == 1) lenS = rnd.next(6, 50);
            else lenS = rnd.next(51, 248);
            string S = randomDigits(lenS, false);
            N = squareString(S);
            break;
        }
        case 9: {
            // Maximal size near our chosen bound: 248-digit root
            int lenS = 248; // ensures N has < 500 digits
            string S = randomDigits(lenS, false);
            N = squareString(S);
            break;
        }
    }

    println(N);
    return 0;
}

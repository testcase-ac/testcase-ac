#include "testlib.h"
using namespace std;

string stripLeadingZeros(const string &s) {
    int i = 0;
    while (i + 1 < (int)s.size() && s[i] == '0') i++;
    return s.substr(i);
}

string mulSmall(const string &s, unsigned long long m) {
    if (m == 0) return "0";
    unsigned long long carry = 0;
    string res;
    res.reserve(s.size() + 20);
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        int d = s[i] - '0';
        unsigned long long cur = (unsigned long long)d * m + carry;
        int digit = int(cur % 10);
        carry = cur / 10;
        res.push_back(char('0' + digit));
    }
    while (carry > 0) {
        int digit = int(carry % 10);
        carry /= 10;
        res.push_back(char('0' + digit));
    }
    reverse(res.begin(), res.end());
    return stripLeadingZeros(res);
}

string addBig(const string &a, const string &b) {
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int carry = 0;
    string res;
    res.reserve(max(a.size(), b.size()) + 1);
    while (i >= 0 || j >= 0 || carry) {
        int da = (i >= 0 ? a[i] - '0' : 0);
        int db = (j >= 0 ? b[j] - '0' : 0);
        int s = da + db + carry;
        res.push_back(char('0' + (s % 10)));
        carry = s / 10;
        i--;
        j--;
    }
    reverse(res.begin(), res.end());
    return stripLeadingZeros(res);
}

string randomBigInt(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string s;
    s.resize(len);
    s[0] = char('1' + rnd.next(0, 8)); // first digit 1-9
    for (int i = 1; i < len; ++i) {
        s[i] = char('0' + rnd.next(0, 9));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_A = 100000000000000000LL; // 1e17

    unsigned long long a = 1;
    string x_str;
    string c_str;

    int type = rnd.next(0, 4);

    if (type == 0) {
        // Tiny numbers
        a = rnd.next(1LL, 9LL);
        int x_len = rnd.next(1, 2);
        int c_len = rnd.next(1, 2);
        if (rnd.next(0, 3) == 0) x_str = "1";
        if (x_str.empty()) x_str = randomBigInt(x_len, x_len);
        c_str = randomBigInt(c_len, c_len);
    } else if (type == 1) {
        // Small numbers
        a = rnd.next(1LL, 1000LL);
        int x_len = rnd.next(1, 3);
        int c_len = rnd.next(1, 3);
        if (rnd.next(0, 4) == 0) x_str = "1";
        if (x_str.empty()) x_str = randomBigInt(x_len, x_len);
        c_str = randomBigInt(c_len, c_len);
    } else if (type == 2) {
        // Medium numbers
        a = rnd.next(1LL, (long long)1e9);
        int x_len = rnd.next(1, 9);
        int c_len = rnd.next(1, 9);
        int special = rnd.next(0, 4);
        if (special == 0) {
            a = 1; // a = 1, so x = b - c
        } else if (special == 1) {
            x_str = "1"; // x = 1, so b - c = a
        }
        if (x_str.empty()) x_str = randomBigInt(x_len, x_len);
        c_str = randomBigInt(c_len, c_len);
    } else if (type == 3) {
        // Large near-limit numbers
        a = rnd.next(1LL, MAX_A);
        int x_len = rnd.next(10, 81);  // ensure product not too long
        int c_len = rnd.next(10, 99);
        if (rnd.next(0, 5) == 0) a = MAX_A; // sometimes max a
        x_str = randomBigInt(x_len, x_len);
        c_str = randomBigInt(c_len, c_len);
    } else { // type == 4, special edge-focused
        int sub = rnd.next(0, 3);
        if (sub == 0) {
            // a = 1, large x
            a = 1;
            int x_len = rnd.next(50, 81);
            int c_len = rnd.next(1, 99);
            x_str = randomBigInt(x_len, x_len);
            c_str = randomBigInt(c_len, c_len);
        } else if (sub == 1) {
            // x = 1, large a and c close to b
            a = rnd.next(1LL, MAX_A);
            x_str = "1";
            int c_len = rnd.next(90, 99);
            c_str = randomBigInt(c_len, c_len);
        } else if (sub == 2) {
            // c = 1, arbitrary a and x
            a = rnd.next(1LL, MAX_A);
            int x_len = rnd.next(1, 81);
            x_str = randomBigInt(x_len, x_len);
            c_str = "1";
        } else {
            // a = MAX_A, random x and c
            a = MAX_A;
            int x_len = rnd.next(1, 81);
            int c_len = rnd.next(1, 99);
            x_str = randomBigInt(x_len, x_len);
            c_str = randomBigInt(c_len, c_len);
        }
    }

    // Safety: if not set by specific case, generate defaults
    if (x_str.empty()) {
        x_str = randomBigInt(1, 5);
    }
    if (c_str.empty()) {
        c_str = randomBigInt(1, 5);
    }

    string delta = mulSmall(x_str, a);     // a * x
    string b_str = addBig(delta, c_str);   // b = a*x + c

    // Ensure constraints: 0 < c < b, b has at most 100 digits
    b_str = stripLeadingZeros(b_str);
    c_str = stripLeadingZeros(c_str);

    // Just in case (should always hold by construction)
    if (b_str.size() > 100) {
        // Extremely unlikely given our bounds; fall back to a simple small case
        a = 4;
        x_str = "3";
        c_str = "8";
        delta = mulSmall(x_str, a);
        b_str = addBig(delta, c_str);
    }

    println(a);
    println(b_str);
    println(c_str);

    return 0;
}

#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Generate a positive decimal number of given length without leading zeros (unless length==1).
string gen_number(int len) {
    if (len == 1) {
        return string(1, char('0' + rnd.next(0, 9)));
    } else {
        string s;
        s += char('0' + rnd.next(1, 9));
        for (int i = 1; i < len; i++)
            s += char('0' + rnd.next(0, 9));
        return s;
    }
}

// Multiply a decimal string 'a' by a non-negative long long 'b'.
string mul_str_by_ll(const string& a, long long b) {
    if (b == 0) return "0";
    vector<int> res;
    long long carry = 0;
    for (int i = int(a.size()) - 1; i >= 0; i--) {
        long long prod = (a[i] - '0') * b + carry;
        res.push_back(int(prod % 10));
        carry = prod / 10;
    }
    while (carry > 0) {
        res.push_back(int(carry % 10));
        carry /= 10;
    }
    string out;
    for (int i = int(res.size()) - 1; i >= 0; i--)
        out += char('0' + res[i]);
    return out;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario to maximize coverage of edge cases.
    int type = rnd.next(0, 5);
    string A_str, B_str;

    switch (type) {
        case 0: { // both small numbers
            int lenA = rnd.next(1, 3);
            int lenB = rnd.next(1, 3);
            A_str = gen_number(lenA);
            B_str = gen_number(lenB);
            if (B_str == "0") B_str = "1";
            break;
        }
        case 1: { // both large numbers
            int lenA = rnd.next(100, 200);
            int lenB = rnd.next(100, 200);
            A_str = gen_number(lenA);
            B_str = gen_number(lenB);
            break;
        }
        case 2: { // divisible case: A = B * factor
            int lenB = rnd.next(1, 50);
            B_str = gen_number(lenB);
            if (B_str == "0") B_str = "1";
            long long factor = rnd.next(1LL, 1000000000LL);
            A_str = mul_str_by_ll(B_str, factor);
            break;
        }
        case 3: { // |A| < |B| => quotient 0
            int lenB = rnd.next(2, 50);
            int lenA = rnd.next(1, lenB - 1);
            B_str = gen_number(lenB);
            A_str = gen_number(lenA);
            break;
        }
        case 4: { // A = 0
            A_str = "0";
            int lenB = rnd.next(1, 10);
            B_str = gen_number(lenB);
            if (B_str == "0") B_str = "1";
            break;
        }
        case 5: { // B = 1 => trivial remainder 0
            int lenA = rnd.next(1, 50);
            A_str = gen_number(lenA);
            B_str = "1";
            break;
        }
    }

    // Randomize signs (but avoid negative zero).
    bool negA = (A_str != "0") && rnd.next(0, 1);
    bool negB = (B_str != "0") && rnd.next(0, 1);
    if (negA) A_str = "-" + A_str;
    if (negB) B_str = "-" + B_str;

    // Output single test case
    println(A_str, B_str);
    return 0;
}

#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    auto toBase = [](int value, int base) -> string {
        string s;
        while (value > 0) {
            int d = value % base;
            char c = (d < 10 ? char('0' + d) : char('a' + (d - 10)));
            s.push_back(c);
            value /= base;
        }
        reverse(s.begin(), s.end());
        return s;
    };

    int scenario = rnd.next(1, 10);
    string X;
    int v;

    switch (scenario) {
        case 1: { // small decimal values
            vector<int> cand = {1, 2, 7, 8, 9, 10, 15, 16, 31, 32, 99};
            v = rnd.any(cand);
            X = to_string(v);
            break;
        }
        case 2: { // random decimal
            v = rnd.next(1, 1000000);
            X = to_string(v);
            break;
        }
        case 3: { // near max decimal
            v = rnd.next(900000, 1000000);
            X = to_string(v);
            break;
        }
        case 4: { // exact maximum decimal
            v = 1000000;
            X = to_string(v);
            break;
        }
        case 5: { // small octal with single leading 0
            v = rnd.next(1, 255);
            string oct = toBase(v, 8);
            X = "0" + oct;
            break;
        }
        case 6: { // general octal with multiple leading zeros
            v = rnd.next(1, 1000000);
            string oct = toBase(v, 8);
            int zeros = rnd.next(1, 3);
            X = string(zeros, '0') + oct;
            break;
        }
        case 7: { // small hex
            v = rnd.next(1, 255);
            string hex = toBase(v, 16);
            X = "0x" + hex;
            break;
        }
        case 8: { // hex near max, optional zero padding after 0x
            v = rnd.next(900000, 1000000);
            string hex = toBase(v, 16);
            int pad = rnd.next(0, 3);
            X = "0x" + string(pad, '0') + hex;
            break;
        }
        case 9: { // hex that must contain letters
            string hex;
            bool hasLetter = false;
            for (int iter = 0; iter < 1000; ++iter) {
                v = rnd.next(1, 1000000);
                hex = toBase(v, 16);
                hasLetter = false;
                for (char c : hex) {
                    if (c >= 'a' && c <= 'f') {
                        hasLetter = true;
                        break;
                    }
                }
                if (hasLetter) break;
            }
            if (!hasLetter) {
                hex = "abc"; // 0xabc = 2748 <= 1e6
            }
            int pad = rnd.next(0, 3);
            X = "0x" + string(pad, '0') + hex;
            break;
        }
        case 10: { // predefined tricky samples
            vector<string> cand = {
                "010",      // octal 8
                "0x10",     // hex 16
                "0x3f6",    // hex 1014
                "0777",     // octal 511
                "0xabc",    // hex 2748
                "000123",   // octal 83
                "0x0001"    // hex 1
            };
            X = rnd.any(cand);
            break;
        }
        default: {
            v = rnd.next(1, 1000000);
            X = to_string(v);
            break;
        }
    }

    println(X);
    return 0;
}

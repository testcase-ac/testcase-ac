#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s;
    int pattern = rnd.next(1, 8);

    switch (pattern) {
    case 1: {
        // Single zero (only case allowed to be "0")
        s = "0";
        break;
    }
    case 2: {
        // Small random length, 1-5
        int n = rnd.next(1, 5);
        s.reserve(n);
        for (int i = 0; i < n; i++)
            s += char('0' + rnd.next(0, 1));
        break;
    }
    case 3: {
        // Leading zeros + random body (will be canonicalized later)
        int lead = rnd.next(1, 5);
        int body = rnd.next(1, 20);
        s.assign(lead, '0');
        for (int i = 0; i < body; i++)
            s += char('0' + rnd.next(0, 1));
        break;
    }
    case 4: {
        // All ones, length 1-60
        int n = rnd.next(1, 60);
        s.assign(n, '1');
        break;
    }
    case 5: {
        // Alternating pattern
        int n = rnd.next(2, 80);
        char start = rnd.next(0, 1) ? '1' : '0';
        s.reserve(n);
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) s += start;
            else s += (start == '0' ? '1' : '0');
        }
        break;
    }
    case 6: {
        // Length multiple of 3, built from random octal digits
        int groups = rnd.next(1, 50); // length up to 150
        s.reserve(groups * 3);
        for (int g = 0; g < groups; g++) {
            int v = rnd.next(0, 7); // one octal digit as 3 bits
            for (int bit = 2; bit >= 0; --bit)
                s += char('0' + ((v >> bit) & 1));
        }
        break;
    }
    case 7: {
        // Medium/large random length 61-200
        int n = rnd.next(61, 200);
        s.reserve(n);
        for (int i = 0; i < n; i++)
            s += char('0' + rnd.next(0, 1));
        break;
    }
    case 8: {
        // Very short, not necessarily multiple of 3, leading ones
        int rem = rnd.next(1, 2);      // 1 or 2 leading bits
        int groups = rnd.next(0, 3);   // 0 to 3 full groups of 3 bits
        int len = rem + 3 * groups;    // total length (1..11)
        s.reserve(len);
        for (int i = 0; i < len; i++) {
            if (i < rem) s += '1';
            else s += char('0' + rnd.next(0, 1));
        }
        break;
    }
    }

    // Enforce canonical binary representation:
    // - Either exactly "0"
    // - Or no leading zeros (first char must be '1')
    if (s != "0") {
        if (s.empty()) s = "1";
        else s[0] = '1';
    }

    println(s);
    return 0;
}

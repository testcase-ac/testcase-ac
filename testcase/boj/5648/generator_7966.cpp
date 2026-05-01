#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = rnd.next(1, 10);
    vector<string> v;
    for (int i = 0; i < n; i++) {
        int typ = rnd.next(0, 3);
        string s;
        if (typ == 0) {
            // pure random number
            int len = rnd.next(1, 12);
            s.resize(len);
            s[0] = char('1' + rnd.next(0, 8));
            for (int j = 1; j < len; j++) s[j] = char('0' + rnd.next(0, 9));
        } else if (typ == 1) {
            // trailing zeros
            int len = rnd.next(2, 12);
            int tz = rnd.next(1, len - 1);
            int hl = len - tz;
            s.resize(hl);
            s[0] = char('1' + rnd.next(0, 8));
            for (int j = 1; j < hl; j++) s[j] = char('0' + rnd.next(0, 9));
            s += string(tz, '0');
        } else if (typ == 2) {
            // palindrome
            int len = rnd.next(1, 12);
            int half = (len + 1) / 2;
            string halfs;
            halfs.resize(half);
            halfs[0] = char('1' + rnd.next(0, 8));
            for (int j = 1; j < half; j++) halfs[j] = char('0' + rnd.next(0, 9));
            s = halfs;
            for (int j = len/2 - 1; j >= 0; j--) s += halfs[j];
        } else {
            // small single-digit
            s = to_string(rnd.next(1, 9));
        }
        v.push_back(s);
    }
    shuffle(v.begin(), v.end());
    println(n);
    for (int i = 0; i < n; i++) {
        printf("%s", v[i].c_str());
        if (i + 1 < n) printf(" ");
    }
    printf("\n");
    return 0;
}

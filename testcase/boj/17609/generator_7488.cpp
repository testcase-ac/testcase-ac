#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool isPal(const string &s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

bool isPseudo(const string &s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] == s[r]) { l++; r--; }
        else {
            // skip l or skip r
            string a = s.substr(l+1, r - l);
            string b = s.substr(l, r - l);
            return isPal(a) || isPal(b);
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 3);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int type = rnd.next(0, 2); // 0: palindrome, 1: pseudo, 2: normal
        int len;
        if (rnd.next(0, 9) == 0) len = rnd.next(21, 30);
        else len = rnd.next(3, 20);

        string s;
        if (type == 0) {
            // generate palindrome
            int alpha = rnd.next(2, 12); // alphabet size = alpha+1
            s.assign(len, 'a');
            for (int i = 0; i <= (len-1)/2; i++) {
                char c = char('a' + rnd.next(0, alpha));
                s[i] = s[len-1-i] = c;
            }
        }
        else if (type == 1) {
            // generate pseudo-palindrome (not palindrome itself)
            int m = len - 1;
            int alpha = rnd.next(2, 12);
            string p(m, 'a');
            for (int i = 0; i <= (m-1)/2; i++) {
                char c = char('a' + rnd.next(0, alpha));
                p[i] = p[m-1-i] = c;
            }
            int ins = rnd.next(0, m);
            s.assign(len, '?');
            // copy before ins
            for (int i = 0; i < ins; i++) s[i] = p[i];
            // copy after ins
            for (int i = ins; i < m; i++) s[i+1] = p[i];
            // set bad char at ins
            char bad;
            do { bad = char('a' + rnd.next(0, alpha)); }
            while (bad == p[ins]);
            s[ins] = bad;
        }
        else {
            // generate normal string, neither palindrome nor pseudo
            int alpha = rnd.next(2, 12);
            do {
                s.clear();
                for (int i = 0; i < len; i++)
                    s.push_back(char('a' + rnd.next(0, alpha)));
            } while (isPal(s) || isPseudo(s));
        }
        println(s);
    }
    return 0;
}

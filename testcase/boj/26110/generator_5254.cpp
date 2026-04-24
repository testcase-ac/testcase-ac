#include "testlib.h"
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool is_pal(const string &s) {
    int i = 0, j = int(s.size()) - 1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // length of string
    int n = rnd.next(5, 20);
    // choose target type: 0,1,2,3 or -1
    vector<int> types = {0,1,2,3,-1};
    int t = rnd.any(types);
    string s;

    if (t >= 0 && t <= 3) {
        // build base palindrome of length m = n - t
        int m = n - t;
        string p;
        int half = m / 2;
        bool odd = (m % 2 == 1);
        // choose alphabet size for diversity
        int alphSize = rnd.next(2, 26);
        // build first half
        for (int i = 0; i < half; i++) {
            char c = char('a' + rnd.next(0, alphSize - 1));
            p.push_back(c);
        }
        // odd center
        if (odd) {
            char c = char('a' + rnd.next(0, alphSize - 1));
            p.push_back(c);
        }
        // mirror
        for (int i = half - 1; i >= 0; i--) {
            p.push_back(p[i]);
        }
        // now p is palindrome of length m
        s = p;
        // insert t extra chars at random positions
        for (int i = 0; i < t; i++) {
            int pos = rnd.next(0, int(s.size()));
            // pick a char from full lowercase
            char c = char('a' + rnd.next(0, 25));
            s.insert(s.begin() + pos, c);
        }
        // ensure s is not accidentally a palindrome if t>=1
        if (t >= 1 && is_pal(s)) {
            // change a random position to a different char
            int pos = rnd.next(0, int(s.size()) - 1);
            char old = s[pos];
            char neu = old;
            while (neu == old) neu = char('a' + rnd.next(0, 25));
            s[pos] = neu;
        }
    } else {
        // type -1: make all chars distinct so LPS = 1 => need >3 deletions
        // pick n distinct letters from a-z
        vector<char> alph;
        for (char c = 'a'; c <= 'z'; c++) alph.push_back(c);
        shuffle(alph.begin(), alph.end());
        s = string(alph.begin(), alph.begin() + n);
    }

    // final check: length
    assert(int(s.size()) == n);
    // output
    println(s);
    return 0;
}

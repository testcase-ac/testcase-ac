#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool ispal(const string &s) {
    int n = s.size();
    for (int i = 0; i < n/2; i++)
        if (s[i] != s[n-1-i]) return false;
    return true;
}

string make_random(int len) {
    string s;
    for (int i = 0; i < len; i++)
        s.push_back(char('a' + rnd.next(0,25)));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(3, 6);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        bool solvable;
        if (ti == 0) solvable = true;
        else if (ti == 1) solvable = false;
        else solvable = rnd.next(0,1);
        vector<string> words;
        int k;
        if (solvable) {
            k = rnd.next(2, 8);
            // choose type of palindrome generation
            if (rnd.next(0,1) == 0) {
                // reversal pair
                int l = rnd.next(1,5);
                string s = make_random(l);
                string t = s;
                reverse(t.begin(), t.end());
                if (s == t) { // ensure nontrivial
                    if (l > 1) s[0] = (s[0]=='a'?'b':'a');
                    t = s;
                    reverse(t.begin(), t.end());
                }
                words.push_back(s);
                words.push_back(t);
            } else {
                // split a palindrome
                int L = rnd.next(3,7);
                string half;
                for (int i = 0; i < L/2; i++)
                    half.push_back(char('a' + rnd.next(0,25)));
                string P = half;
                if (L % 2 == 1) P.push_back(char('a' + rnd.next(0,25)));
                for (int i = int(half.size())-1; i >= 0; i--)
                    P.push_back(half[i]);
                int cut = rnd.next(1, L-1);
                words.push_back(P.substr(0, cut));
                words.push_back(P.substr(cut));
            }
            // fill the rest with random words
            for (int i = 2; i < k; i++) {
                int len = rnd.next(1,5);
                words.push_back(make_random(len));
            }
        } else {
            k = rnd.next(1, 8);
            // generate k words with no palindrome pair
            while ((int)words.size() < k) {
                int len = rnd.next(1,5);
                string w = make_random(len);
                bool ok = true;
                for (auto &u : words) {
                    string rw = w; reverse(rw.begin(), rw.end());
                    if (rw == u) { ok = false; break; }
                    if (ispal(w+u) || ispal(u+w)) { ok = false; break; }
                }
                if (ok) words.push_back(w);
            }
        }
        shuffle(words.begin(), words.end());
        println(k);
        for (auto &w : words) println(w);
    }
    return 0;
}

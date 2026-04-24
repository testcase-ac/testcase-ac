#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = rnd.next(0, 2);
    int N = rnd.next(2, 10);
    vector<string> s;

    if (type == 1) {
        // Impossible: each string uses a unique letter only
        vector<char> alph(26);
        iota(alph.begin(), alph.end(), 'a');
        shuffle(alph.begin(), alph.end());
        for (int i = 0; i < N; i++) {
            char c = alph[i];
            int len = rnd.next(2, 5);
            string t(len, c);
            s.push_back(t);
        }
    } else if (type == 2) {
        // Force zero deletion: one string ends with c, another starts with c
        char c = char('a' + rnd.next(0, 25));
        int len0 = rnd.next(2, 8);
        string s0;
        for (int i = 0; i < len0 - 1; i++) s0 += char('a' + rnd.next(0, 25));
        s0 += c;
        int len1 = rnd.next(2, 8);
        string s1;
        s1 += c;
        for (int i = 1; i < len1; i++) s1 += char('a' + rnd.next(0, 25));
        s.push_back(s0);
        s.push_back(s1);
        // Fill the rest with random unique strings
        set<string> used = {s0, s1};
        while ((int)s.size() < N) {
            int len = rnd.next(2, 8);
            string t;
            for (int i = 0; i < len; i++) t += char('a' + rnd.next(0, 25));
            if (used.insert(t).second) s.push_back(t);
        }
    } else {
        // Pure random strings
        set<string> used;
        while ((int)s.size() < N) {
            int len = rnd.next(2, 10);
            string t;
            for (int i = 0; i < len; i++) t += char('a' + rnd.next(0, 25));
            if (used.insert(t).second) s.push_back(t);
        }
    }

    println(N);
    for (auto &str : s) println(str);
    return 0;
}
